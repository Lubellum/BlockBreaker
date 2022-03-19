// [1]ヘッダーをincludeする場所
#include <stdio.h>  // [1-?]標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-?]標準ライブラリヘッダーをインクルードする
#include <string.h> // [1-?]文字列操作ヘッダーをインクルードする
#include <time.h>   // [1-?]時間ヘッダーをインクルードする
#include "conio.h"  // [1-?]コンソール入出力ヘッダーを擬似的にインクルード
#include "kbhit.h"  // [1-?]kbhitヘッダーを擬似的にインクルード

// [2]定数を宣言する場所
#define FIELD_WIDTH  (15) // [2-?]フィールドの幅を宣言
#define FIELD_HEIGHT (30) // [2-?]フィールドの高さを宣言
#define PADDLE_WIDTH (3)  // [2-?]パドルの幅を宣言する

#define FPS          (10)         // [2-?]1秒あたりの描画頻度を宣言する
#define INTERVAL     (1000 / FPS) // [2-?]描画間隔(ミリ秒)を宣言する

#define PADDLE_WIDTH (3)  // [2-?]パドルの幅を宣言する

// [3]列挙定数を宣言する場所
// [3-?]タイルの種類を宣言する
enum {
    TILE_NONE,   // [3-?-?]何も無い
    TILE_BLOCK,  // [3-?-?]ブロック
    TILE_BALL,   // [3-?-?]ボール
    TILE_PADDLE, // [3-?-?]パドル
    TILE_MAX     // [3-?-?]種類の数
};

// [4]構造体を宣言する場所
// [4-?]ベクトル構造体を宣言する
typedef struct {
    int x, y;
}VEC2;

// [4-?]ボールの構造体を宣言する
typedef struct {
    VEC2 position;
    VEC2 direction;
}BALL;

// [5]変数を宣言する場所
// [5-?]タイルのアスキーアートを宣言する
const char *tileAA[] = {
    "・",  // [5-?-?]TILE_NONE, 何も無い
    "🟫",  // [5-?-?]TILE_BLOCK, ブロック
    "🔵",  // [5-?-?]TILE_BALL, ボール
    "回",  // [5-?-?]TILE_PADDLE, パドル
};

int field  [FIELD_HEIGHT][FIELD_WIDTH]; // [5-?]フィールドを宣言する
int screen [FIELD_HEIGHT][FIELD_WIDTH]; // [5-?]画面を宣言する

BALL ball;
// VEC2 ball.position  = { 0, FIELD_HEIGHT / 4 }; //[5-?]ボールの座標を初期化する
// VEC2 ball.direction = { 1, 1 };                // [5-?]ボールの進行方向を宣言する

VEC2 paddlePosition = {( FIELD_WIDTH - PADDLE_WIDTH ) / 2, FIELD_HEIGHT - 4}; // [5-?]パドルの座標を宣言する

// [6]関数を宣言する場所
// [6-?]画面を描画する関数を宣言
void DrawScreen(){
    // [6-?-?]画面にフィールドをコピーする
    memcpy(screen, field, sizeof field);

    // [6-?-?]画面にボールを描画する
    screen[ball.position.y][ball.position.x] = TILE_BALL;

     // [6-?-?]パドルの幅だけ反復する
    for(int x = 0; x < PADDLE_WIDTH; x++){
        screen[paddlePosition.y][paddlePosition.x + x] = TILE_PADDLE;
    }

    // system("reset");
    
    for(int x = 0; x < FIELD_WIDTH + 2; x++){
        printf("⬜️");
    }
    // [6-?-?]上の壁の描画が終わり次第改行
    printf("\n");
    // [6-?]全ての行を反復する
    for(int y = 0; y < FIELD_HEIGHT; y++){
      // [6-?-?]左の壁を描画する
      printf("⬜️");
      // [6-?-?]全ての列を反復する
      for(int x = 0; x < FIELD_WIDTH; x++){
        // [6-?-?]対象のマスを描画する
        printf("%s", tileAA[screen[y][x]]);
      }
      printf("⬜️"); // [6-?-?]右の壁を描画する
      // [6-?-?]1行描画する毎に改行
      printf("\n");
    }
}
// [6-?]ゲームをリセットする関数を宣言する
void Reset(){
    // [6-?-?]フィールドの上1/4を反復する
    for(int y = 0; y < FIELD_HEIGHT / 4; y++){
        // [6-?-?]全ての列を反復する
        for(int x = 0; x < FIELD_WIDTH; x++){
            // [6-?-?]対象の座標にブロックを配置する
            field[y][x] = TILE_BLOCK;
        }
    }
    // [6-?-?]画面を描画する関数を呼び出す
    DrawScreen();
}

// [6-?]対象の座標がフィールドの範囲内かどうか判定する関数を宣言する
bool InsideField(VEC2 _v){
    // [6-?]対象の座標がフィールドの範囲内かどうかを返す
    return 
        (_v.x >= 0)               // 左端より右かどうか
        && (_v.x < FIELD_WIDTH)   // 右端より左かどうか
        && (_v.y >= 0)            // 下端より上かどうか
        && (_v.y < FIELD_HEIGHT); // 上端より下かどうか
};

// [6-?]ボールとブロックが当たったかどうか判定する関数を宣言する
bool BallIntersectBlocks(){
    // [6-?-?]ボールの座標が先頭行かどうか判定する
    if(ball.position.y <= 0){
        return false; // 当たらなかったという結果を返す
    } else {
        // [6-?-?]ボールの左右1マスを反復する
        for(int x = ball.position.x -1; x <= ball.position.x + 1; x++){
            // [6-?-?]ボールの1マス上の左右の座標を取得する
            VEC2 position = {
                x,
                ball.position.y - 1
            };

            // [6-?-?]対象の座標がフィールドの範囲内でないかどうか判定する
            if(!InsideField(position)){
                continue; // [6-?-?]次の座標へスキップする
            }

            // [6-?-?]対象の座標にブロックがあるかどうか判定する
            if(field[position.y][position.x] == TILE_BLOCK){
                return true; // [6-?-?]当たったという結果を返す
            }
        }
    }
    return false; // [6-?-?]当たらなかったという結果を返す
}

// [6-?]メッセージを表示する関数を宣言する
void Message(const char *_message){
    DrawScreen();           // [6-?-?]画面を再描画する
    printf("%s", _message); // [6-?-?]メッセージを表示する
    _getch();               // [6-?-?]キーボード入力を待つ
}

// [6-?]プログラムの実行開始を宣言する
int main (){
    Reset(); // [6-?]ゲームをリセットする関数を呼び出す

    // [6-?-?]前回の時間を宣言する
    clock_t lastClock = clock();

    // [6-?-?]メインループを追加する
    while (1){
        // [6-?-?]現在の時間を宣言する
        clock_t newClock = clock();

        // [6-?-?]描画時間になったかどうか判定する
        if (newClock >= lastClock + INTERVAL){

            // [6-?-?]次のボールの座標を宣言する
            VEC2 nextBallPosition = {
                ball.position.x += ball.direction.x, // [6-?-?]ボールを横に移動させる
                ball.position.y += ball.direction.y // [6-?-?]ボールを縦に移動させる
            };

            // [6-?-?]ボールが上端と当たったかどうか判定する
            if(nextBallPosition.y <= 0){
                ball.direction.y = 1;
            }

            // [6-?-?]ボールが下端と当たったかどうか判定する
            if(nextBallPosition.y >= FIELD_HEIGHT - 1){
                ball.direction.y = -1;

                // [6-?-?]ゲームオーバーのメッセージを表示する
                Message("GAME OVER"); // (const char *_message)
            }

            // [6-?-?]ボールが左の壁と当たったかどうか判定する
            if(nextBallPosition.x <= 0){
                ball.direction.x = 1;
            }

            // [6-?-?]ボールが右の壁と当たったかどうか判定する
            if(nextBallPosition.x >= FIELD_WIDTH - 1){
                ball.direction.x = -1;
            }

            ball.position = nextBallPosition; // [6-?-?]次のボールの座標を適用する

            // [6-?-?]ボールがパドルの上の座標に当たったかどうか判定する
            if(
                //[6-?-?]ボールの座標がパドルの上の行かどうか
                (ball.position.y == paddlePosition.y - 1)

                //[6-?-?]ボールの座標がパドルの左端よりも右か
                && (ball.position.x == paddlePosition.x - 1)

                //[6-?-?]ボールの座標がパドルの右端よりも左か
                && (ball.position.x < paddlePosition.x + PADDLE_WIDTH + 1)
            ){
                ball.direction.y = -1; // [6-?-?]ボールの進行方向を上にする

                //[6-?-?]パドルの中心のX座標を宣言する
                int paddleCenterX = paddlePosition.x + PADDLE_WIDTH / 2;

                //[6-?-?]ボールがパドルの左端に当たったら
                if(ball.position.x < paddleCenterX){
                    ball.direction.x = -1; //[6-?-?]ボールを左に跳ね返す
                }
                
                //[6-?-?]ボールがパドルの右端に当たったら
                else if(ball.position.x > paddleCenterX){
                    ball.direction.x = 1; //[6-?-?]ボールを右に跳ね返す
                }
            }

            // [6-?-?]ボールとブロックが当ったかどうか判定する
            if(BallIntersectBlocks()){
                ball.direction.y = 1; // [6-?-?]ボールを下へ跳ね返す

                // [6-?-?]ボールの左右1マスを反復する
                for(int x = ball.position.x - 1; x < ball.position.x + 1; x++){
                    // [6-?-?]対象の座標を宣言する
                    VEC2 position = { x, ball.position.y - 1 };

                    // [6-?-?]対象の座標がフィールドの範囲内でないかどうか判定する
                    if(!InsideField(position)){
                        continue; // [6-?-?]次の座標へスキップする
                    } else {
                        // [6-?-?]対象のブロックを削除する
                        field[position.y][position.x] = TILE_NONE;
                    }
                }
            }

            lastClock = newClock; // [6-?-?]前回の時間を更新する

            DrawScreen(); // [6-?-?]画面を再描画する
        }

        // [6-?-?]キーボード入力があったかどうか判定する
        if(_kbhit()){
            // [6-?-?]入力されたキーによって分岐する
                switch (_getch()){
                case 'a': // [6-?-?]aキーが押されたら左に移動する
                    paddlePosition.x--;
                    break;
                case 'd': // [6-?-?]dキーが押されたら右に移動する
                    paddlePosition.x++;
                    break;
            }

            // [6-?-?]パドルが左の壁にめり込んだかどうか判定する
            if(paddlePosition.x < 0){
                paddlePosition.x = 0; // パドルをフィールド内に押し戻す
            }

            // [6-?-?]パドルが右の壁にめり込んだかどうか判定する
            if(paddlePosition.x + PADDLE_WIDTH >= FIELD_WIDTH){
                paddlePosition.x = FIELD_WIDTH - PADDLE_WIDTH; // パドルをフィールド内に押し戻す
            }

            DrawScreen();
        }
    }
}