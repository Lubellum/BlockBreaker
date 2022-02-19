// [1]ヘッダーをincludeする場所
#include <stdio.h>  // [1-?]標準入出力ヘッダーをインクルードする
#include <string.h> // [1-?]文字列操作ヘッダーをインクルードする

// [2]定数を宣言する場所
#define FIELD_WIDTH  (15) // [2-?]フィールドの幅を宣言
#define FIELD_HEIGHT (20) // [2-?]フィールドの高さを宣言

#define PADDLE_WIDTH (3)  // [2-?]パドルの幅を宣言する

// [3]列挙定数を宣言する場所
// [3-?]タイルの種類を宣言する
enum {
    TILE_NONE,   // [3-?-?]何も無い
    TILE_BLOCK,  // [3-?-?]ブロック
    TILE_PADDLE, // [3-?-?]パドル
    TILE_MAX     // [3-?-?]種類の数
};

// [4]構造体を宣言する場所
// [4-?]ベクトル構造体を宣言する
typedef struct {
    int x, y;
}VEC2;


// [5]変数を宣言する場所
// [5-?]タイルのアスキーアートを宣言する
const char *tileAA[] =  {
    "・",  // [5-?-?]TILE_NONE, 何も無い
    "🟫",  // [5-?-?]TILE_BLOCK, ブロック
    "回",  // [5-?-?]TILE_PADDLE, パドル
};

int field  [FIELD_WIDTH][FIELD_HEIGHT]; // [5-?]フィールドを宣言する
int screen [FIELD_WIDTH][FIELD_HEIGHT]; // [5-?]画面を宣言する

VEC2 paddlePosition; // [5-?]パドルの座標を宣言する

// [6]関数を宣言する場所
// [6-?]画面を描画する関数を宣言
void DrawScreen(){
    // [6-?-?]画面にフィールドをコピーする
    memcpy(screen, field, sizeof field);

    // [6-?-?]パドルの幅だけ反復する
    // 初期化して描画の位置まではあっている。はず。あとは何故描画が上手くいっていないのか？
    for(int x = 0; x < PADDLE_WIDTH; x++){
        screen[paddlePosition.y][paddlePosition.x + x] = TILE_PADDLE;
        // screen[4][10] = TILE_PADDLE;
    }

    // [6-?-?]上の壁を描画する
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
    // [6-?-?]フィールドの上の方を反復する
    for(int y = 0; y < 6; y++){
        // [6-?-?]全ての列を反復する
        for(int x = 0; x < FIELD_WIDTH; x++){
            // [6-?-?]対象の座標にブロックを配置する
            field[y][x] = TILE_BLOCK;
        }
    }

    // [6-?-?]パドルの座標を初期化する
    // paddlePosition.x = (FIELD_WIDTH - PADDLE_WIDTH) / 2;
    // paddlePosition.y = FIELD_HEIGHT - 2;

    // [6-?-?]画面を描画する関数を呼び出す
    DrawScreen();
}
// [6-?]プログラムの実行開始を宣言する
int main (){
    // [6-?]ゲームをリセットする関数を呼び出す
    Reset();
    // [6-?-?]メインループを追加する
    while (1){
      
    }
}