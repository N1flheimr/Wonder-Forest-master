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
	//前フレームの四隅のマップチップ座標
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
	//player重力への仮移動
	player.rightUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;
	player.leftUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;

	//playerが地面に着いたら
	if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK || MAP[player.rightUnderY][player.rightUnderX] == BLOCK) {
		player.posY = 704 - player.R;	//地面の座標
		gravity = 0;
		player.isJump = 0;
	}

	//oldがNONEのときのローカル変数
	int oldTopNone = MAP[player.oldleftTopY][player.oldleftTopX] == NONE && MAP[player.oldrightTopY][player.oldrightTopX] == NONE;
	int oldUnderNone = MAP[player.oldleftUnderY][player.oldleftUnderX] == NONE && MAP[player.oldrightUnderY][player.oldrightUnderX] == NONE;

	//着地直前
	//oldTopとoldUnderがNONEのとき
	if (oldTopNone && oldUnderNone) {

		//playerの仮移動
		player.rightUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;
		player.leftUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;

		//playerがブロックより上にいるとき
		if (player.posY - player.R < (player.rightTopY + 1) * BLOCK_SIZE) {

			//playerの足元がブロックなら
			if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK2 || MAP[player.rightUnderY][player.rightUnderX] == BLOCK2) {
				gravity = 0;	//重力リセット
				player.velY = 0;	//ジャンプスピードリセット
			}
		}
	}

	//playerの足元に何もなければ
	if (MAP[player.leftUnderY][player.leftUnderX] == NONE && MAP[player.rightUnderY][player.rightUnderX] == NONE) {
		isStop = 0;	//落下する
	}

	//着地
	//oldTopとoldUnderがNONEのとき
	if (oldTopNone && oldUnderNone) {

		//playerの仮移動
		player.rightUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;
		player.leftUnderY = (player.posY + player.R - 1 + gravity) / BLOCK_SIZE;

		//playerがブロックより上にいるとき
		if (player.posY - player.R + 30 < (player.rightTopY + 1) * BLOCK_SIZE) {

			//playerの足元がブロックなら
			if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK2 || MAP[player.rightUnderY][player.rightUnderX] == BLOCK2) {
				gravity = 0;	//重力リセット
				player.velY = 0;	//ジャンプスピードリセット
				player.isJump = 0;	//ジャンプ終わり
				isStop = 1;	//ブロックに乗っている
			}
		}
	}

	//右からのめりこみ対策
	//oldUnderがNONEかつplayerがブロックより下にいるとき
	if (oldUnderNone && player.posY - player.R + 63 > (player.rightTopY + 1) * BLOCK_SIZE) {

		//playerの左下がブロックにめりこんでるなら
		if (MAP[player.leftUnderY][player.leftUnderX] == BLOCK2) {

			//playerの右側がNONEなら
			if (MAP[player.rightUnderY][player.rightUnderX] == NONE && MAP[player.rightTopY][player.rightTopX] == NONE) {
				isStop = 0;	//落下する
			}
		}
	}

	//左からのめりこみ対策
	//oldUnderがNONEかつplayerがブロックより下にいるとき
	if (oldUnderNone && player.posY - player.R + 63 > (player.rightTopY + 1) * BLOCK_SIZE) {

		//playerの右下がブロックにめりこんでるなら
		if (MAP[player.rightUnderY][player.rightUnderX] == BLOCK2) {

			//playerの左側がNONEなら
			if (MAP[player.leftUnderY][player.leftUnderX] == NONE && MAP[player.leftTopY][player.leftTopX] == NONE) {
				isStop = 0;	//落下する
			}
		}
	}
}