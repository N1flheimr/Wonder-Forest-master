#include "DxLib.h"
#include "WindowSetting.h"

//WindowSetting.h 変数の定義
const char TITLE[] = "LC1B_29_ライアン_ウィドジャジャ: タイトル";
const int WIN_WIDTH = 1408;
const int WIN_HEIGHT = 768;

//WindowSetting.h 関数の定義
void WindowSetting() {
	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x25, 0x25, 0x25);

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);
}