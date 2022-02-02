// [1]ヘッダーをincludeする場所
#include <stdio.h> // [1-?]標準入出力ヘッダーをインクルードする

// [2]定数を宣言する場所
#define FIELD_WIDTH  (40) // [2-?]フィールドの幅を宣言
#define FIELD_HEIGHT (20) // [2-?]フィールドの高さを宣言

// [3]列挙定数を宣言する場所
// [3-?]タイルの種類を宣言する
enum {
    TILE_NONE,  // [3-?-?]何も無い
    TILE_BLOCK, // [3-?-?]ブロック
    TILE_MAX    // [3-?-?]種類の数
};

// [4]構造体を宣言する場所

// [5]変数を宣言する場所
// [5-?]タイルのアスキーアートを宣言する
const char *tileAA[] =  {
    "・", // TILE_NONE, 何も無い
    "■",  // TILE_BLOCK, ブロック
};

int field  [FIELD_WIDTH][FIELD_HEIGHT]; // [5-?]フィールドを宣言する
int screen [FIELD_WIDTH][FIELD_HEIGHT]; // [5-?]画面を宣言する

// [6]関数を宣言する場所
// [6-?]画面を描画する関数を宣言
void DrawScreen(){
    // [6-?]全てのマスを反復する
    for(int y = 0; y < FIELD_HEIGHT; y++){
      for(int x = 0; x < FIELD_WIDTH; x++){
        // [6-?-?]対象のマスを描画する
          printf("%s", tileAA[screen[y][x]]);
      }
    // [6-?-?]1行描画する毎に改行
      printf("\n");
    }
}
// [6-?]ゲームをリセットする関数を宣言する
void Reset(){
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