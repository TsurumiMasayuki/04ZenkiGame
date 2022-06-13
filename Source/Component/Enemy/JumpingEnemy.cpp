#include "JumpingEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void JumpingEnemy::onStart()
{
	cylinderCoord.z = getTransform().getLocalPosition().z;
	getUser().setTag("Enemy");

	// コライダー付与
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(true);
	// 重力の無効化
	x->setUseGravity(false);

	intervalTimer.setMaxTime(interval);
}

void JumpingEnemy::onUpdate()
{
	// 基準座標取得
	Vec3 position = getUser().getTransform().getLocalPosition();

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//回転速度をラジアンに変換
	float radRotateSpeed = MathUtility::toRadian(velocity.y);

	// 円筒座標変換
	position = CoordConverter::cartesianToCylinder(position);

	// ジャンプさせる
	float jumpVec = sinf(cycleCnt);
	// マイナスになったら0に強制変換
	if (jumpVec <= 0)
	{
		jumpVec = 0;
	}

	// 座標セット
	position.x = radius + jumpVec * 3;
	position.y += radRotateSpeed * deltaTime;
	position.z += velocity.z * deltaTime;	// zは指定スピードで進む

	//円筒座標をデカルト座標に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	//座標を適用
	getUser().getTransform().setLocalPosition(cartCoord);

	// 
	cycleCnt += deltaTime;

	// タイマーの更新
	intervalTimer.update();
}

void JumpingEnemy::init(Vec3 position, float speedZ, float speedY, float radius)
{
	// 初期座標セット
	getUser().getTransform().setLocalPosition(position);

	// 速度セット
	velocity.y = speedY;
	velocity.z = speedZ;

	// 円筒半径セット
	this->radius = radius;
}

void JumpingEnemy::setJumpParameter(float hight, float interval)
{
	this->hight = hight;
	this->interval = interval;

	intervalTimer.setMaxTime(interval);
}
