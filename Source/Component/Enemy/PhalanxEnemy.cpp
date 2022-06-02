#include "PhalanxEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

void PhalanxEnemy::onStart()
{

}

void PhalanxEnemy::onUpdate()
{
	for (int i = 0; i < vec_object.size(); i++)
	{
		// 基準座標取得
		Vec3 position = vec_object[i]->getTransform().getLocalPosition();

		//deltaTimeを取得
		float deltaTime = GameDevice::getGameTime().getDeltaTime();
		//回転速度をラジアンに変換
		float radRotateSpeed = MathUtility::toRadian(swingWidth * sinf(swingCnt - (1 / vec_object.size() * i)));

		//移動
		cylinderCoord.x = radius;	// xは円筒半径で固定
		cylinderCoord.y += radRotateSpeed * deltaTime;
		cylinderCoord.z += speedZ * deltaTime - (float)i * 1.0f;	// zは指定スピードで進む - 敵一体

		//円筒座標をデカルト座標に変換
		Vec3 cartCoord = CoordConverter::cylinderToCartesian(cylinderCoord);

		//座標を適用
		vec_object[i]->getTransform().setLocalPosition(cartCoord);

		//回転
		vec_object[i]->getTransform().setLocalAngles(
			Vec3(0.0f,
				0.0f,
				MathUtility::toDegree(cylinderCoord.y))
		);
	}

	// 本体が死んだら
	if (vec_object[mainUnit]->getComponent<TestEnemy>()->getDead())
	{
		// 全部殺す
		for (auto x : vec_object)
		{
			x->getComponent<TestEnemy>()->setDead(true);
			//x->setActive(false);
		}
	}

	// 反復用
	swingCnt += 0.01f;
}

void PhalanxEnemy::init(Vec3 position, int length, int mainUnit, float radius, float speedZ)
{
	// 配列の再構築
	vec_object.resize(length);

	// 敵生成
	for (int i = 0; i < length; i++)
	{
		// 生成
		vec_object[i] = new GameObject(getUser().getGameMediator());
	}

	// 本体番号セット
	if (mainUnit < length - 1)
	{
		this->mainUnit = mainUnit;
	}
	else
	{
		this->mainUnit = length - 1;
	}
	
	// 円筒の半径セット
	this->radius = radius;

	// 速度セット
	this->speedZ = speedZ;
}
