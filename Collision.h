#pragma once
#include  "Player.h"
#include "Enemy.h"


struct CircleCollision
{
	float a;	//三平方の定理のa
	float b;	//三平方の定理のb
	float c;	//三平方の定理のc
};

class Collision
{
public:
	Collision();
	void Init();
	void Update(Player &player, Enemy &enemy);

private:
	int decrementValue = 10;
	CircleCollision playerToEnemyCollision;
	CircleCollision bulletToEnemyCollision;
};

