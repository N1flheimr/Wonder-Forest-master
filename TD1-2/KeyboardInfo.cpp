#include "DxLib.h"
#include "KeyboardInfo.h"

//KeyboardSetting.h 変数の定義
char keys[256] = { 0 };
char oldkeys[256] = { 0 };

//KeyboardSetting.h 関数の定義
void KeyboardInfo() {
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}