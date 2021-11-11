#include "map.h"
#include "playerMovement.h"

const int BLOCK_SIZE = 64;

int mapHandle[2];

int oldTopNone = 0;
int oldUnderNone = 0;

const int MAP[12][22]{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void playerCornersInfo() {
	player.rightTopX = (player.posX + player.R - 1) / BLOCK_SIZE;
	player.rightTopY = (player.posY - player.R) / BLOCK_SIZE;
	player.rightUnderX = (player.posX + player.R - 1) / BLOCK_SIZE;
	player.rightUnderY = (player.posY + player.R - 1) / BLOCK_SIZE;
	player.leftTopX = (player.posX - player.R) / BLOCK_SIZE;
	player.leftTopY = (player.posY - player.R) / BLOCK_SIZE;
	player.leftUnderX = (player.posX - player.R) / BLOCK_SIZE;
}

void oldPlayerCornersInfo() {
	//�O�t���[���̎l���̃}�b�v�`�b�v���W
	player.oldleftTopX = player.leftTopX;
	player.oldleftTopY = player.leftTopY;
	player.oldleftUnderX = player.leftUnderX;
	player.oldleftUnderY = player.leftUnderY;
	player.oldrightTopX = player.rightTopX;
	player.oldrightTopY = player.rightTopY;
	player.oldrightUnderX = player.rightUnderX;
	player.oldrightUnderY = player.rightUnderY;
}



void mapChipCollision() {
	//player�d�͂ւ̉��ړ�
	player.rightUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;
	player.leftUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;

	//player���n�ʂɒ�������
	if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK || MAP[player.rightUnderY][player.rightUnderX] == BLOCK) {
		player.posY = 704 - player.R;	//�n�ʂ̍��W
		gravity = 0;
		player.isJump = 0;
	}

	//old��NONE�̂Ƃ��̃��[�J���ϐ�
	int oldTopNone = MAP[player.oldleftTopY][player.oldleftTopX] == NONE && MAP[player.oldrightTopY][player.oldrightTopX] == NONE;
	int oldUnderNone = MAP[player.oldleftUnderY][player.oldleftUnderX] == NONE && MAP[player.oldrightUnderY][player.oldrightUnderX] == NONE;

	//���n���O
	//oldTop��oldUnder��NONE�̂Ƃ�
	if (oldTopNone && oldUnderNone) {

		//player�̉��ړ�
		player.rightUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;
		player.leftUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;

		//player���u���b�N����ɂ���Ƃ�
		if (player.posY - player.R < (player.rightTopY + 1) * BLOCK_SIZE) {

			//player�̑������u���b�N�Ȃ�
			if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK2 || MAP[player.rightUnderY][player.rightUnderX] == BLOCK2) {
				gravity = 0;	//�d�̓��Z�b�g
				player.velY = 0;	//�W�����v�X�s�[�h���Z�b�g
			}
		}
	}

	//player�̑����ɉ����Ȃ����
	if (MAP[player.leftUnderY][player.leftUnderX] == NONE && MAP[player.rightUnderY][player.rightUnderX] == NONE) {
		isStop = 0;	//��������
	}

	//���n
	//oldTop��oldUnder��NONE�̂Ƃ�
	if (oldTopNone && oldUnderNone) {

		//player�̉��ړ�
		player.rightUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;
		player.leftUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;

		//player���u���b�N����ɂ���Ƃ�
		if (player.posY - player.R + 30 < (player.rightTopY + 1) * BLOCK_SIZE) {

			//player�̑������u���b�N�Ȃ�
			if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK2 || MAP[player.rightUnderY][player.rightUnderX] == BLOCK2) {
				gravity = 0;	//�d�̓��Z�b�g
				player.velY = 0;	//�W�����v�X�s�[�h���Z�b�g
				player.isJump = 0;	//�W�����v�I���
				isStop = 1;	//�u���b�N�ɏ���Ă���
			}
		}
	}

	//�E����̂߂肱�ݑ΍�
	//oldUnder��NONE����player���u���b�N��艺�ɂ���Ƃ�
	if (oldUnderNone && player.posY - player.R + 63 > (player.rightTopY + 1) * BLOCK_SIZE) {

		//player�̍������u���b�N�ɂ߂肱��ł�Ȃ�
		if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK2) {

			//player�̉E����NONE�Ȃ�
			if (MAP[player.rightUnderY][player.rightUnderX] == NONE && MAP[player.rightTopY][player.rightTopX] == NONE) {
				isStop = 0;	//��������
			}
		}
	}

	//������̂߂肱�ݑ΍�
	//oldUnder��NONE����player���u���b�N��艺�ɂ���Ƃ�
	if (oldUnderNone && player.posY - player.R + 63 > (player.rightTopY + 1) * BLOCK_SIZE) {

		//player�̉E�����u���b�N�ɂ߂肱��ł�Ȃ�
		if (MAP[player.rightUnderY][player.rightUnderX] == BLOCK2) {

			//player�̍�����NONE�Ȃ�
			if (MAP[player.leftUnderY][player.leftUnderX] == NONE && MAP[player.leftTopY][player.leftTopX] == NONE) {
				isStop = 0;	//��������
			}
		}
	}
}