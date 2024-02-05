#include "Player.h"
#include "Bullet.h"
#include "Novice.h"
#include "Clamp.h"

Player::Player()
{
	pos_ = { 0,0 };
	radius_ = 30;
	velocity_ = { 0,0 };
	color_ = 0;
	canShoot_ = true;
	shootInterval_ = 0;
	mousePos_ = { 0,0 };

	isAlive_ = false;
	respwaninterval_ = 0;
}

Player::~Player()
{
	for (auto* b : bullet) {
		delete b;
	}
}

void Player::Init()
{
	pos_ = { 640,600 };
	velocity_ = { 0,0 };
	bullet.clear();
	canShoot_ = true;
	shootInterval_ = kShotInterval;
	mousePos_ = { 0,0 };
	color_ = 0xa0d8efFF;
	isAlive_ = true;
	respwaninterval_ = kPlayerRespawninterval;
}

void Player::Update(char* keys)
{
	if (isAlive_) {
		//プレイヤーの上下左右移動
		if (keys[DIK_W] || keys[DIK_UPARROW])
		{
			velocity_.y = -kPlayerMoveSpeed;
		}
		if (keys[DIK_A] || keys[DIK_LEFTARROW])
		{
			velocity_.x = -kPlayerMoveSpeed;
		}
		if (keys[DIK_S] || keys[DIK_DOWNARROW])
		{
			velocity_.y = kPlayerMoveSpeed;
		}
		if (keys[DIK_D] || keys[DIK_RIGHTARROW])
		{
			velocity_.x = kPlayerMoveSpeed;
		}


		//自機の移動
		pos_.x += velocity_.x;
		pos_.y += velocity_.y;


		pos_.x = Clamp(0 + float(radius_), 1280 - float(radius_), pos_.x);
		pos_.y = Clamp(0 + float(radius_), 720 - float(radius_), pos_.y);

		velocity_ = { 0,0 };


		//マウスの座標
		Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);

		//弾の発射
		if (Novice::IsPressMouse(0) && canShoot_ && isAlive_)
		{
			//弾の発射間隔の調整
			canShoot_ = false;
			Bullet* newBullet = new Bullet();
			newBullet->Init();

			//弾の生成

			bullet.push_back(newBullet);
			newBullet->SetIsShot(true);

			//弾の情報を代入
			newBullet->SetPos({ float(pos_.x),float(pos_.y) });
			newBullet->SetVelocity({ 10.0f,10.0f });

			//マウスの方向に向けて発射
			float angle = atan2f(float(mousePos_.y) - pos_.y, float(mousePos_.x) - pos_.x);
			newBullet->SetVector({ cosf(angle), sinf(angle) });

			//弾の発射間隔の時間設定
			shootInterval_ = kShotInterval;
		}
	}
	else
	{
		respwaninterval_--;
		if(respwaninterval_ <= 0)
		{
			isAlive_ = true;
			respwaninterval_ = kPlayerRespawninterval;
		}
	}

	auto iterator = bullet.begin();
	while (iterator != bullet.end())
	{
		//弾の更新処理
		(*iterator)->Update();
		//弾を消す処理
		if ((*iterator)->GetIsShot())
		{
			++iterator;
		}
		else
		{
			iterator = bullet.erase(iterator);
		}
	}

	//弾の発射間隔
	if (!canShoot_)
	{
		shootInterval_--;
		if (shootInterval_ <= 0)
		{
			canShoot_ = true;
		}
	}
}

void Player::Draw()
{
	//弾の描画
	auto iterator = bullet.begin();
	while (iterator != bullet.end())
	{
		//弾の描画処理
		(*iterator)->Draw();
		++iterator;
	}

	if (isAlive_) {
		//プレイヤーの描画
		Novice::DrawEllipse(
			int(pos_.x), int(pos_.y),
			radius_, radius_,
			0.0f,
			color_,
			kFillModeSolid
		);
	}

	/* 説明 */
	////操作方法
	//Novice::ScreenPrintf(150, 100, "{ [WASD Key] || [Arrow Key] } : move { Left Click } : shoot");
	//Novice::ScreenPrintf(150, 120, "{ R Key } : Initialize ");
	//Novice::ScreenPrintf(150, 140, "{ E Key } : change bullet type");
	//Novice::ScreenPrintf(150, 160, "{ Left Click } : shoot");
	//Novice::ScreenPrintf(300, 620, "bulletsOffScreenCount_ = %d : if(bulletsOffScreenCount_ == 100){ NextScene }", bulletsOffScreenCount_);
}
