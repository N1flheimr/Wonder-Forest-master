#pragma once

typedef struct BOSS {
	int posX;
	int posY;
	int posX2;
	int posY2;
	int actType;
};

extern BOSS boss;

void bossAction();