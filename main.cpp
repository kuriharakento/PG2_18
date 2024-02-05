#include <Novice.h>

#include "Collision.h"
#include "Enemy.h"
#include "Player.h"

const char kWindowTitle[] = "LC1A_13_クリハラ_ケント_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Player* player = new Player();
	player->Init();

	Enemy* enemy1 = new Enemy();
	enemy1->Init();

	Enemy* enemy2 = new Enemy();
	enemy2->Init();
	enemy2->SetPos({ enemy2->GetPos().x,200 });

	Collision* collision = new Collision();


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys[DIK_R] && !preKeys[DIK_R])
		{
			Enemy::EnemyDeath = false;
			enemy1->SetIsAlive(true);
			enemy2->SetIsAlive(true);
		}
		player->Update(keys);
		if (!Enemy::EnemyDeath) {
			enemy1->Update();
			enemy2->Update();
		}
		collision->Update(*player, *enemy1);
		collision->Update(*player, *enemy2);
		if (!enemy1->GetIsAlive() || !enemy2->GetIsAlive())
		{
			Enemy::EnemyDeath = true;
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->Draw();
		if (!Enemy::EnemyDeath) {
			enemy1->Draw();
			enemy2->Draw();
		}

		Novice::ScreenPrintf(100, 100, " R : enemy respawn");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;
	delete enemy1;
	delete enemy2;
	delete collision;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
