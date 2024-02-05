#pragma once
#include <vector>
#include "IntVector2.h"
#include "Vector2.h"

const int kPlayerMoveSpeed = 4;
const int kShotInterval = 12;
const int kPlayerRespawninterval = 120;

class Bullet;
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(char* keys);
	void Draw();

	//アクセッサ
	//ゲッター
	Vector2 GetPos() { return pos_; }
	int GetRadius() { return radius_; }
	Vector2 GetVelocity() { return velocity_; }
	bool GetIsAlive() { return isAlive_; }
	std::vector<Bullet*> GetBullet() { return bullet; }

	//セッター
	void SetPos(Vector2 pos) { this->pos_ = pos; }
	void SetVelocity(Vector2 velocity) { this->velocity_ = velocity; }
	void SetIsAlive(bool isAlive) { this->isAlive_ = isAlive; }

private:
	//プレイヤーの情報
	Vector2 pos_;
	int radius_;
	Vector2 velocity_;
	unsigned int color_;

	bool isAlive_;
	int respwaninterval_;

	//マウスの座標
	IntVector2 mousePos_;

	//弾の情報
	std::vector<Bullet*> bullet;
	int shootInterval_;
	bool canShoot_;

};

