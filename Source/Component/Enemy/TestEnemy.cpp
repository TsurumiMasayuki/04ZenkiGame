#include "TestEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

#include "btBulletDynamicsCommon.h"

void TestEnemy::onStart()
{
	m_CylinderCoord.z = getTransform().getLocalPosition().z;
	getUser().setTag("Enemy");
}

void TestEnemy::onUpdate()
{
	return;

	// 基準座標取得
	Vec3 position = getUser().getTransform().getLocalPosition();

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();
	//回転速度をラジアンに変換
	float radRotateSpeed = MathUtility::toRadian(rotateSpeed);

	//移動
	m_CylinderCoord.x = radius;
	m_CylinderCoord.y += radRotateSpeed * deltaTime;
	m_CylinderCoord.z += speed * deltaTime;

	//円筒座標をデカルト座標に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(m_CylinderCoord);

	//座標を適用
	getTransform().setLocalPosition(cartCoord);

	//回転
	getTransform().setLocalAngles(
		Vec3(0.0f,
			0.0f,
			MathUtility::toDegree(m_CylinderCoord.y))
	);
}

void TestEnemy::init(float speed, float rotateSpeed, float radius, Vec3 centerPoint)
{
	this->speed = speed;
	this->rotateSpeed = rotateSpeed;
	this->radius = radius;
	this->centerPoint = centerPoint;
}