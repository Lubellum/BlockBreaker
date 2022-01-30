// [1]ヘッダーをincludeする場所

// [2]定数を宣言する場所
#define FIELD_WIDTH  (8) // [2-?]フィールドの幅を宣言
#define FIELD_HEIGHT (8) // [2-?]フィールドの高さを宣言

// [3]列挙定数を宣言する場所

// [4]構造体を宣言する場所

// [5]変数を宣言する場所
int field  [FIELD_WIDTH][FIELD_HEIGHT]; // [5-?]フィールドを宣言する
int screen [FIELD_WIDTH][FIELD_HEIGHT]; // [5-?]画面を宣言する

// [6]関数を宣言する場所
// [6-?]画面を描画する関数を宣言
void DrawScreen(){

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