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

	//ウィンドウの設定
	WindowSetting();

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// 画像などのリソースデータの変数宣言と読み込み
	LoadDivGraph("resources/map.png", 2, 2, 1, 64, 64, mapHandle);

	// ゲームループで使う変数の宣言

	for (int i = 0; i < MAX_BULLET; i++) {
		bullet.isShot[i] = false;
	}

	

	// ゲームループ
	while (true) {
		//マウスとキーボードの入力状態
		KeyboardInfo();
		MouseInput();

		// 画面クリア
		ClearDrawScreen();

		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		playerCornersInfo();

		supportMovement();

		mapChipCollision();

		//近接攻撃
		playerMelee(player.posX, player.posY, player.direction, player.R, attack.posX, attack.posY, attack.posX2, attack.posY2, attack.rangeX, attack.rangeY, mouseX, attack.pattern, attack.timer);

		//遠距離攻撃
		playerShoot(player.posX, player.posY, bullet.X, bullet.Y, bullet.speed, bullet.CD, bullet.isShot, direction.x, direction.y, bullet.currentAngle, bullet.angle);

		//移動処理の関数
		playerMovement(player.posX, player.posY, player.state, player.velX, player.direction, attack.pattern, attack.timer);

		playerJump();

		//ダッシュ
		playerDash();

		//プレイーやの状態
		playerStates(player.velX, player.state, attack.pattern);

		oldPlayerCornersInfo();

		// 描画処理
		//player
		DrawBox(player.posX - player.R, player.posY - player.R,
			player.posX + player.R, player.posY + player.R,
			GetColor(255, 255, 255), true
		);

		//サポートキャラ
		DrawCircle(support.posX, support.posY, support.R,
			GetColor(255, 255, 255), true
		);

		//boss
		DrawBox(boss.posX, boss.posY, boss.posX2, boss.posY2, GetColor(255, 255, 255), true);

		//boss弱点
		DrawBox(1050, 300, 1100, 350, GetColor(0, 0, 0), true);

		//HPゲージ
		DrawBox(350, 25, 1150, 50, GetColor(0, 0, 0), true);

		//playerの方向の矢印
			//右向き
		if (player.direction == RIGHT) {
			DrawTriangle(player.posX + player.R + 16, player.posY - player.R + 16,
				player.posX + player.R + 16, player.posY + player.R - 16,
				player.posX + player.R * 2, player.posY + player.R - 32,
				GetColor(255, 255, 255), true
			);
		}

		//左向き
		else if (player.direction == LEFT) {
			DrawTriangle(player.posX - player.R - 16, player.posY - player.R + 16,
				player.posX - player.R - 16, player.posY + player.R - 16,
				player.posX - player.R * 2, player.posY + player.R - 32,
				GetColor(255, 255, 255), true
			);
		}

		//マップ描画
		for (int y = 0; y < 12; y++) {

			for (int x = 0; x < 22; x++) {

				for (int i = 0; i < 2; i++) {

					if (MAP[y][x] == i + 1) {
						DrawGraph(x * 64, y * 64, mapHandle[i], true);
					}
				}
			}
		}

		//HPゲージ
		DrawBox(350, 25, 1150, 50, GetColor(0, 0, 0), true);
		for (int i = 0; i < MAX_BULLET; i++) {
			if (bullet.isShot[i] == true) {
				DrawCircle(bullet.X[i], bullet.Y[i], bullet.R, GetColor(255, 255, 255), true);
			}
		}

		//デバッグ用
		//近接攻撃のヒットボックス
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

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == true) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}