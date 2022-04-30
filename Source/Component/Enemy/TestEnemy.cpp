#include "TestEnemy.h"
#include "Device/GameDevice.h"

void TestEnemy::onStart()
{
	// それぞれ座標初期化
	position = Vec3(0,0,0);
	speed = 1.0f;
	targetPos = Vec3(0,0,0);
}

void TestEnemy::onUpdate()
{
	// 基準座標取得
	position = getUser().getTransform().getLocalPosition();

	// 目標座標取得
	targetPos = object->getTransform().getLocalPosition();

	// 移動方向算出
	moveVec = targetPos - position;
	moveVec = moveVec.normalized();

	// 座標更新
	position += moveVec * speed * GameDevice::getGameTime().getDeltaTime();
	// 座標セット
	getUser().getTransform().setLocalPosition(position);
}

void TestEnemy::SetTarget(GameObject* object)
{
	this->object = object;
}
