#pragma once
#include "Vector2.h"
#include "Novice.h"
#define _USE_MATH_DEFINES
#include "math.h"

const int kEnemyRadius = 30;

class Enemy
{
public:
	Enemy();
	void Init();
	void Update();
	void Draw();

	//静的メンバー変数
	static bool EnemyDeath;

	//アクセッサ
	//ゲッター
	Vector2 GetPos() { return pos_; }
	int GetRadius() { return radius_; }
	Vector2 GetVelocity(){ return velocity_; }
	Vector2 GetVector() { return vector_; }
	bool GetIsAlive() { return isAlive_; }

	//セッター
	void SetPos(Vector2 pos) { this->pos_ = pos; }
	void SetVelocity(Vector2 velocity) { this->velocity_ = velocity; }
	void SetVector(Vector2 vector) { this->vector_ = vector; }
	void SetRadius(int radius) { this->radius_ = radius; }
	void SetIsAlive(bool isAlive) { this->isAlive_ = isAlive; }

private:
	//座標、半径、速度、
	Vector2 pos_;
	int radius_;
	Vector2 velocity_;
	Vector2 vector_;
	unsigned int color_;

	//生きているか
	bool isAlive_;
};
