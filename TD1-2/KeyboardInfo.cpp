#include "DxLib.h"
#include "KeyboardInfo.h"

//KeyboardSetting.h �ϐ��̒�`
char keys[256] = { 0 };
char oldkeys[256] = { 0 };

//KeyboardSetting.h �֐��̒�`
void KeyboardInfo() {
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}