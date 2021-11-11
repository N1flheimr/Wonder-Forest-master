#pragma once

// 最新のキーボード情報用の宣言
extern char keys[256];
// 1ループ(フレーム)前のキーボード情報の宣言
extern char oldkeys[256];

// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存関数の宣言
extern void KeyboardInfo();