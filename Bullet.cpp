#include "Bullet.h"

#include "Novice.h"

Bullet::Bullet()
{
	pos_ = { 0,0 };
	vector_ = { 0,0 };
	velocity_ = { 0,0 };
	radius_ = kBulletRadius;
	isShot_ = false;
	color_ = 0;
}

void Bullet::Init()
{
	pos_ = { 0,0 };
	vector_ = { 0,0 };
	velocity_ = { 0,0 };
	radius_ = kBulletRadius;
	isShot_ = false;
	color_ = 0x96e9faff;
}


void Bullet::Update()
{
	if (isShot_)
	{
		pos_.x += vector_.x * velocity_.x;
		pos_.y += vector_.y * velocity_.y;

		if (pos_.x < 0 - radius_ || pos_.x  > 1280 + radius_ || pos_.y < 0 - radius_ || pos_.y > 720 + radius_)
		{
			isShot_ = false;
		}
	}
}

void Bullet::Draw()
{

	if (isShot_)
	{

		Novice::DrawEllipse(
			int(pos_.x), int(pos_.y),
			int(radius_), int(radius_),
			0.0f,
			color_,
			kFillModeSolid
		);


	}
}
