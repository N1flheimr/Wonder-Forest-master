#include "playerCombat.h"
#include "MouseInput.h"
#include "playerMovement.h"
#include "WindowSetting.h"
#include "map.h"
#include <math.h>
#define SECOND 50


BLT bullet{

};

ATK attack{
		0,				//atkPattern
		SECOND / 2,		//atkTimer
		72,				//rangeX
		72,				//rangeY
		0,				//posX
		0,				//posY
		0,				//posX2
		0				//posY2
};

Vector2 direction{
	0,
	0
};

void playerMelee(int playerX, int playerY, int& playerDirection, int playerR, int& atkX, int& atkY, int& atkX2, int& atkY2, int& rangeX, int rangeY, int mouseX, int& atkPattern, int& atkTimer) {

	if (mouseClick[LEFT] == true && oldMouseClick[LEFT] == false) {
		atkPattern++;
		atkTimer = SECOND / 2;
		atkTimer--;
		if (mouseX >= playerX + 32 / 2) {
			playerDirection = RIGHT;
		}
		else if (mouseX < playerX + 32 / 2) {
			playerDirection = LEFT;
		}
	}

	//近接距離のヒットボックス
	if (playerDirection == RIGHT && atkPattern > 0 && atkPattern < 4 && atkTimer>0) {
		atkX = playerX + playerR;
		atkY = playerY - playerR - 4;
		atkX2 = atkX + rangeX;
		atkY2 = atkY + rangeY;
	}
	if (playerDirection == LEFT && atkPattern > 0 && atkPattern < 4 && atkTimer>0) {
		atkX = playerX - playerR;
		atkY = playerY - playerR - 4;
		atkX2 = atkX - rangeX;
		atkY2 = atkY + rangeY;
	}
	if (atkPattern == 3) {
		rangeX = 96;
	}
	else {
		rangeX = 72;
	}

	if (atkPattern > 3 && atkTimer > 15) {
		atkPattern = 1;
	}

	if (atkTimer < SECOND / 2) {
		atkTimer--;
		if (atkTimer < 0) {
			atkTimer = SECOND / 2;
			atkPattern = 0;

		}
	}
}

void playerShoot(int playerX, int playerY, int* bulletX, int* bulletY, int& bulletSpeed, int& bulletCD, bool* isShot, float& directionX, float& directionY, float& angle, float* angle2) {
	directionX = mouseX - support.posX;
	directionY = mouseY - support.posY;
	bulletSpeed = 20;
	angle = atan2(directionY, directionX);

	if (mouseClick[RIGHT] == true) {
		bulletCD--;
	}
	if (mouseClick[RIGHT] == false && oldMouseClick[RIGHT] == false) {
		bulletCD = 3;
	}

	for (int i = 0; i < MAX_BULLET; i++) {
		if (isShot[i] == false) {
			if (bulletCD < 0) {
				angle2[i] = angle;
				isShot[i] = true;
				bulletX[i] = support.posX;
				bulletY[i] = support.posY;
				bulletCD = 3;
			}
		}
		if (isShot[i] == true) {
			bulletX[i] += (float)cos(angle2[i]) * bulletSpeed;
			bulletY[i] += (float)sin(angle2[i]) * bulletSpeed;
		}
		if (bulletY[i] < 0 - 16) {
			isShot[i] = false;
		}
		else if (bulletY[i] > WIN_HEIGHT + bullet.R) {
			isShot[i] = false;
		}
		else if (bulletX[i] > WIN_WIDTH-BLOCK_SIZE - bullet.R) {
			isShot[i] = false;
		}
		else if (bulletX[i] < 0 - bullet.R) {
			isShot[i] = false;
		}
	}
}