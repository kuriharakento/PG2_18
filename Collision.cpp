#include "Collision.h"

#include "Bullet.h"
using namespace std;

Collision::Collision()
{
	playerToEnemyCollision = { 0.0f,0.0f,0.0f };
	bulletToEnemyCollision = { 0.0f,0.0f,0.0f };
}

void Collision::Init()
{
	playerToEnemyCollision = { 0.0f,0.0f,0.0f };
	bulletToEnemyCollision = { 0.0f,0.0f,0.0f };
}

void Collision::Update(Player& player, Enemy& enemy)
{
	//プレイヤーと敵の衝突判定
	if (player.GetIsAlive() && enemy.GetIsAlive())
	{
		playerToEnemyCollision.a = powf(player.GetPos().x - enemy.GetPos().x, 2);
		playerToEnemyCollision.b = powf(player.GetPos().y - enemy.GetPos().y, 2);
		playerToEnemyCollision.c = powf(float(player.GetRadius() + enemy.GetRadius()), 2);

		if (playerToEnemyCollision.c >= playerToEnemyCollision.a + playerToEnemyCollision.b)
		{
			player.SetIsAlive(false);
		}
	}

	//敵と弾の当たり判定
	const std::vector<Bullet*> myCopy = player.GetBullet();
	std::vector<Bullet*>::const_iterator i = myCopy.begin();
	while (i != myCopy.end())
	{
		//表示されているなら実行する
		if ((*i)->GetIsShot() && enemy.GetIsAlive())
		{
			bulletToEnemyCollision.a = powf((*i)->GetPos().x - enemy.GetPos().x, 2);
			bulletToEnemyCollision.b = powf((*i)->GetPos().y - enemy.GetPos().y, 2);
			bulletToEnemyCollision.c = powf((*i)->GetRadius() + float(enemy.GetRadius()), 2);

			//判定
			if (bulletToEnemyCollision.c >= bulletToEnemyCollision.a + bulletToEnemyCollision.b)
			{
				//当たっていたので弾と敵を消す
				(*i)->SetIsShot(false);
				enemy.SetIsAlive(false);
			}

		}
		i++;
	}
}

