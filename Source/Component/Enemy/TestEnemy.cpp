#include "TestEnemy.h"
#include "Device/GameDevice.h"

void TestEnemy::onStart()
{
}

void TestEnemy::onUpdate()
{
	// 基準座標取得
	position = getUser().getTransform().getLocalPosition();



	// 座標更新
	position += moveVec * speed * GameDevice::getGameTime().getDeltaTime();
	// 座標セット
	getUser().getTransform().setLocalPosition(position);
}

void TestEnemy::init(float angle, float speed = 1.0f, float radius = 11.0f, Vec3 centerPoint = Vec3(0, 0, 0))
{
	this->angle = angle;
	this->speed = speed;
	this->rasius = radius;
	this->centerPoint = centerPoint;
}