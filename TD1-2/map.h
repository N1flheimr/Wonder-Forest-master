#pragma once

//�}�b�v�̒�`
enum MAP {
	NONE,	//0
	BLOCK,	//1
	BLOCK2,	//2
};

extern int mapHandle[2];

extern const int BLOCK_SIZE;

extern const int MAP[12][22];

extern int oldTopNone;
extern int oldUnderNone;

//player�l���̃}�b�v�`�b�v���W�̎擾
void playerCornersInfo();
void oldPlayerCornersInfo();
void mapChipCollision();