#pragma once
enum PlState {
	IDLE = 0, MOVING = 1, DASH = 2, ATTACKING = 3
};

extern int gravity;
extern bool isStop;

typedef struct PL {
	int posX;
	int posY;
	int posX2;
	int posY2;
	int velX;			//velocity=スピード
	int velY;
	int direction;		//向き
	int dashSpeed;
	int R;				//半径
	int leftTopX;
	int leftTopY;
	int leftUnderX;
	int leftUnderY;
	int rightTopX;
	int rightTopY;
	int rightUnderX;
	int rightUnderY;
	int oldleftTopX;
	int oldleftTopY;
	int oldleftUnderX;
	int oldleftUnderY;
	int oldrightTopX;
	int oldrightTopY;
	int oldrightUnderX;
	int oldrightUnderY;
	int state;
	int isJump;
	int isDash;
	const int size = 64;
};

struct SPT {
	int posX;
	int posY;
	int R;
};

extern PL player;

extern SPT support;

void supportMovement();

void playerMovement(int& playerX, int& playerY, int playerState, int& speed, int& direction, int& atkPattern, int& atkTimer);

void playerJump();

void playerDash();

void playerStates(int& playerSpeed, int& playerState, int atkPattern);