#include "playerMovement.h"
#include "KeyboardInfo.h"
#include "DxLib.h"
#include "WindowSetting.h"
#include "MouseInput.h"
#include "map.h"
#include "playerCombat.h"

int gravity = 0;
bool isStop = 0;

PL player = {
		300,	//posX
		0,		//posY
		0,		//posX2
		0,		//posY2
		0,		//velX
		0,		//velY
		RIGHT,	//direction (0 = LEFT, 1 = RIGHT)
		0,		//dashSpeed
		32,		//radius
		0,		//leftTopX
		0,		//leftTopY
		0,		//leftUnderX
		0,		//leftUnderY
		0,		//rightTopX
		0,		//rightTopY
		0,		//rightUnderX
		0,		//rightUnderY
		0,		//oldleftTopX
		0,		//oldleftTopY
		0,		//oldleftUnderX
		0,		//oldleftUnderY
		0,		//oldrightTopX
		0,		//oldrightTopY
		0,		//oldRightUnderX
		0,		//oldRightUnderY
		0,		//state
		0,		//isJump
		0		//isDash
};

SPT support{
	0,
	0,
	16
};

void supportMovement() {
	support.posX = player.posX - player.R * 2;
	support.posY = player.posY - player.R * 2;
}

void playerMovement(int& playerX, int& playerY, int playerState, int& speed, int& direction, int& atkPattern, int& atkTimer) {
	speed = 0;

	if (keys[KEY_INPUT_D] == true && playerState != 3) {
		speed = 8;
		playerX += speed;
		direction = RIGHT;
	}

	if (keys[KEY_INPUT_A] == true && playerState != 3) {
		speed = 8;
		playerX -= speed;
		direction = LEFT;
	}

	//ブロックから降りる
	if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0) {
		isStop = 0;
	}
}

void playerJump() {
	//ジャンプ
	if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0) {
		if (player.isJump == 0) {
			player.velY = 35;
			player.isJump = 1;
		}
	}
	//ジャンプしたら
	if (player.isJump == 1) {
		player.posY -= player.velY;
		player.velY -= 1;
	}
	else {
		player.isJump = 0;
	}
}

void playerDash() {
	//ダッシュ
	if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) {
		attack.pattern = 0;
		attack.timer = 25;
		if (player.isDash == 0) {
			player.dashSpeed = 14;
			player.isDash = 1;
		}
	}
	//ダッシュしたら
	if (player.isDash == 1) {
		//右向きなら
		if (player.direction == RIGHT) {
			player.posX += player.dashSpeed;
			player.dashSpeed -= 1;
			if (player.dashSpeed <= 0) {
				player.isDash = 0;	//ダッシュ終了
			}
		}
		//左向きなら
		else if (player.direction == LEFT) {
			player.posX -= player.dashSpeed;
			player.dashSpeed -= 1;
			if (player.dashSpeed <= 0) {
				player.isDash = 0;	//ダッシュ終了
			}
		}
	}
	//重力
	if (isStop == 0) {
		gravity += 1;
		player.posY += gravity;
	}
}

void playerStates(int& playerSpeed, int& playerState, int atkPattern) {
	if (playerSpeed == 0) {
		playerState = IDLE;
	}
	if (playerSpeed == 8) {
		playerState = MOVING;
	}
	if (atkPattern > 0) {
		playerState = ATTACKING;
	}
}