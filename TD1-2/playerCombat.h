#pragma once
const int MAX_BULLET = 100;

typedef struct BLT {
	bool isShot[MAX_BULLET];
	int X[MAX_BULLET];
	int Y[MAX_BULLET];
	const int R = 8;
	int CD;					//CD = クールダウン
	int speed;
	float currentAngle;
	float angle[MAX_BULLET];
};

extern BLT bullet;

struct ATK {
	int pattern;			//攻撃パターン
	int timer;
	int rangeX;
	int rangeY;
	int posX;
	int posY;
	int posX2;
	int posY2;
};

extern ATK attack;

struct Vector2 {
	float x;
	float y;
};

extern Vector2 direction;

void playerMelee(int playerX, int playerY, int& playerDirection, int playerSize, int& atkX, int& atkY, int& atkX2, int& atkY2, int& rangeX, int rangeY, int mouseX, int& atkPattern, int& atkTimer);
void playerShoot(int playerX, int playerY, int* bulletX, int* bulletY, int& bulletSpeed, int& bulletCD, bool* isShot, float& directionX, float& directionY, float& angle, float* angle2);