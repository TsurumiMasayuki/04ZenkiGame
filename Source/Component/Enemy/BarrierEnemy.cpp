#include "BarrierEnemy.h"
#include "Component/Physics/SphereColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void BarrierEnemy::onStart()
{
	// 基準座標取得
	position = getUser().getTransform().getLocalPosition();
	rotation = getUser().getTransform().getLocalAngles();

	// 敵としてタグ付け
	getUser().setTag("Enemy");

	// コライダー付与
	auto x = getUser().addComponent<SphereColliderBt>();
	x->setTrigger(false);
	// 重力の無効化
	x->setUseGravity(false);

}

void BarrierEnemy::onUpdate()
{
	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	// X軸回転速度をラジアンに変換
	velocity.y = MathUtility::toRadian(velocity.y);

	// 移動量加算
	position += velocity * deltaTime;

	// 円筒座標をデカルト座標系に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	getUser().getTransform().setLocalPosition(cartCoord);
}

void BarrierEnemy::init(Vec3 position, float speedZ, float speedY, float radius)
{
	this->position = position;
	velocity.y = speedY;
	velocity.z = speedZ;
	this->radius = radius;
}
