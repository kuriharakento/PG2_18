#pragma once
#include <vector>

#include "Vector2.h"
#include "Novice.h"

const int kBulletRadius = 7;

class Bullet
{
public:
	Bullet();
	void Init();
	void Update();
	void Draw();

	//アクセッサ
	//ゲッター
	Vector2 GetPos() { return pos_; }
	Vector2 GetVector() { return vector_; }
	Vector2 GetVelocity() { return velocity_; }
	float GetRadius() { return radius_; }

	bool GetIsShot() { return isShot_; }

	//セッター
	void SetPos(Vector2 pos) { this->pos_ = pos; }
	void SetVelocity(Vector2 velocity) { this->velocity_ = velocity; }
	void SetVector(Vector2 vector) { this->vector_ = vector; }
	void SetIsShot(bool isShot) { this->isShot_ = isShot; }

private:
	//弾の座標、向き、速度、弾の種類,
	Vector2 pos_;
	Vector2 vector_;
	Vector2 velocity_;

	//半径、色、発射されているかのフラグ
	float radius_;
	unsigned int color_;
	bool isShot_;
};

