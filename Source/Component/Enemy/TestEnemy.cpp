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

	// コライダー付与
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(true);
	// 重力の無効化
	x->setUseGravity(false);

	testTimer.setMaxTime(5.0f);

	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void TestEnemy::onUpdate()
{
	// 死んでいたら一定時間後に蘇生
	if (isDead && testTimer.isTime())
	{
		isDead = false;

		// 当たり判定のON
		getUser().getComponent<BoxColiiderBt>()->setActive(true);
	}

	// タイマーの更新
	testTimer.update();

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

void TestEnemy::setDead(bool isDead)
{
	this->isDead = isDead;
	pAudio->setAudio("EnemyDown");

	pAudio->play();

	// 当たり判定のOFF
	getUser().getComponent<BoxColiiderBt>()->setActive(false);

	testTimer.reset();
}
