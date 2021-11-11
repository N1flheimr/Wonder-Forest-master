#include "DxLib.h"
#include "WindowSetting.h"
#include "KeyboardInfo.h"
#include "playerMovement.h"
#include "MouseInput.h"
#include "playerCombat.h"
#include "map.h"
#include "bossAI.h"

#define SECOND 50

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	//�E�B���h�E�̐ݒ�
	WindowSetting();

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	LoadDivGraph("resources/map.png", 2, 2, 1, 64, 64, mapHandle);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	for (int i = 0; i < MAX_BULLET; i++) {
		bullet.isShot[i] = false;
	}

	

	// �Q�[�����[�v
	while (true) {
		//�}�E�X�ƃL�[�{�[�h�̓��͏��
		KeyboardInfo();
		MouseInput();

		// ��ʃN���A
		ClearDrawScreen();

		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		playerCornersInfo();

		supportMovement();

		mapChipCollision();

		//�ߐڍU��
		playerMelee(player.posX, player.posY, player.direction, player.R, attack.posX, attack.posY, attack.posX2, attack.posY2, attack.rangeX, attack.rangeY, mouseX, attack.pattern, attack.timer);

		//�������U��
		playerShoot(player.posX, player.posY, bullet.X, bullet.Y, bullet.speed, bullet.CD, bullet.isShot, direction.x, direction.y, bullet.currentAngle, bullet.angle);

		//�ړ������̊֐�
		playerMovement(player.posX, player.posY, player.state, player.velX, player.direction, attack.pattern, attack.timer);

		playerJump();

		//�_�b�V��
		playerDash();

		//�v���C�[��̏��
		playerStates(player.velX, player.state, attack.pattern);

		oldPlayerCornersInfo();

		// �`�揈��
		//player
		DrawBox(player.posX - player.R, player.posY - player.R,
			player.posX + player.R, player.posY + player.R,
			GetColor(255, 255, 255), true
		);

		//�T�|�[�g�L����
		DrawCircle(support.posX, support.posY, support.R,
			GetColor(255, 255, 255), true
		);

		//boss
		DrawBox(boss.posX, boss.posY, boss.posX2, boss.posY2, GetColor(255, 255, 255), true);

		//boss��_
		DrawBox(1050, 300, 1100, 350, GetColor(0, 0, 0), true);

		//HP�Q�[�W
		DrawBox(350, 25, 1150, 50, GetColor(0, 0, 0), true);

		//player�̕����̖��
			//�E����
		if (player.direction == RIGHT) {
			DrawTriangle(player.posX + player.R + 16, player.posY - player.R + 16,
				player.posX + player.R + 16, player.posY + player.R - 16,
				player.posX + player.R * 2, player.posY + player.R - 32,
				GetColor(255, 255, 255), true
			);
		}

		//������
		else if (player.direction == LEFT) {
			DrawTriangle(player.posX - player.R - 16, player.posY - player.R + 16,
				player.posX - player.R - 16, player.posY + player.R - 16,
				player.posX - player.R * 2, player.posY + player.R - 32,
				GetColor(255, 255, 255), true
			);
		}

		//�}�b�v�`��
		for (int y = 0; y < 12; y++) {

			for (int x = 0; x < 22; x++) {

				for (int i = 0; i < 2; i++) {

					if (MAP[y][x] == i + 1) {
						DrawGraph(x * 64, y * 64, mapHandle[i], true);
					}
				}
			}
		}

		//HP�Q�[�W
		DrawBox(350, 25, 1150, 50, GetColor(0, 0, 0), true);
		for (int i = 0; i < MAX_BULLET; i++) {
			if (bullet.isShot[i] == true) {
				DrawCircle(bullet.X[i], bullet.Y[i], bullet.R, GetColor(255, 255, 255), true);
			}
		}

		//�f�o�b�O�p
		//�ߐڍU���̃q�b�g�{�b�N�X
		if (attack.pattern > 0) {
			DrawBox(attack.posX, attack.posY, attack.posX2, attack.posY2, GetColor(255, 255, 255), false);
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "gravity=%d", gravity);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "speedY=%d", player.velY);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "dash=%d", player.isDash);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "LeftTop map[%d][%d]", player.leftTopY, player.leftTopX);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "rightTop map[%d][%d]", player.rightTopY, player.rightTopX);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "LeftUnder map[%d][%d]", player.leftUnderY, player.leftUnderX);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "rightUnder map[%d][%d]", player.rightUnderY, player.rightUnderX);
		DrawFormatString(0, 140, GetColor(255, 255, 255), "rightUnder posy%d posx%d", player.posY, player.posX);
		DrawFormatString(0, 320, GetColor(255, 255, 255), "rightTopY=%d", (player.rightTopY + 1) * BLOCK_SIZE);
		DrawFormatString(0, 512, GetColor(255, 255, 255), "rightTopY=%d", (player.rightTopY + 1) * BLOCK_SIZE);
		DrawFormatString(0, 180, GetColor(255, 255, 255), "stop=%d", isStop);
		DrawFormatString(0, 200, GetColor(255, 255, 255), "jump=%d", player.isJump);
		DrawFormatString(0, 220, GetColor(255, 255, 255), "supportX= %d, supportY= %d", support.posX, support.posY);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == true) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}