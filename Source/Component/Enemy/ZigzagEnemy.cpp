#include "ZigzagEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

void Zigzagenemy::onStart()
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

	wrapTimer.setMaxTime(3.0f);
}

void Zigzagenemy::onUpdate()
{
	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	// X軸回転速度をラジアンに変換
	velocity.y = MathUtility::toRadian(velocity.y);

	// 一定時間で方向転換
	if (wrapTimer.isTime())
	{
		wrap();
	}

	// 移動量加算
	Vec3 tmpVel = Vec3(velocity.x, velocity.y * dir, velocity.z);
	position += tmpVel * deltaTime;

	// 円筒座標をデカルト座標系に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	getUser().getTransform().setLocalPosition(cartCoord);

	//回転
	getTransform().setLocalAngles(Vec3(0.0f, 0.0f, MathUtility::toDegree(position.y) + 180.0f));

	// タイマーの更新
	wrapTimer.update();
}

void Zigzagenemy::init(Vec3 position, float speedY, float speedZ, float radius)
{
	// 初期値セット
	this->position = position;
	velocity = Vec3(0, speedY, speedZ);
	this->radius = radius;
}

void Zigzagenemy::wrap()
{
	// 移動方向反転
	dir = -dir;

	// タイマーリセット
	wrapTimer.reset();
}
