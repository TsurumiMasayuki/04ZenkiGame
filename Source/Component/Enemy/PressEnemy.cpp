#include "PressEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

void PressEnemy::onStart()
{
	// 基準座標取得
	Vec3 position = getUser().getTransform().getLocalPosition();

	// 敵としてタグ付け
	getUser().setTag("Enemy");

	// コライダー付与
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(false);
	// 重力の無効化
	x->setUseGravity(false);

}

void PressEnemy::onUpdate()
{
	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	// X軸回転速度をラジアンに変換
	velocity.y = MathUtility::toRadian(velocity.y);

	if (targetObj)
	{
		Vec3 targetPos = targetObj->getTransform().getLocalPosition();

		if (targetPos.distance(position) < 5.0f)
		{
			press();
		}
	}

	// 下降＆上昇
	if (isPress && position.x)
	{
		velocity.x = -3.0f * deltaTime;
	}
	else
	{
		velocity.x = 1.0f * deltaTime;
	}

	// 移動量加算
	Vec3 tmpVel = Vec3(velocity.x, velocity.y, velocity.z);
	position += tmpVel * deltaTime;

	// 円筒座標をデカルト座標系に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	getUser().getTransform().setLocalPosition(cartCoord);

	//回転
	getTransform().setLocalAngles(Vec3(0.0f, 0.0f, MathUtility::toDegree(position.y) + 180.0f));

}

void PressEnemy::init(Vec3 position, float speedY, float speedZ, float radius)
{
	// 初期値セット
	this->position = Vec3(position.x + 5.0f, position.y, position.z);
	velocity = Vec3(0, speedY, speedZ);
	this->radius = radius;
}

void PressEnemy::press()
{
	isPress = !isPress;
}
