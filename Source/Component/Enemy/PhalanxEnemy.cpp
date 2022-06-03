#include "PhalanxEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

#include "Utility/ModelGameObjectHelper.h"

void PhalanxEnemy::onStart()
{

}

void PhalanxEnemy::onUpdate()
{
	// 基準座標取得
	//Vec3 position = vec_object[i]->getTransform().getLocalPosition();

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	for (int i = 0; i < vec_object.size(); i++)
	{
		//回転速度をラジアンに変換
		float radRotateSpeed = MathUtility::toRadian(swingWidth * sinf(swingCnt - (10 / vec_object.size() * i)));

		Vec3 tmp_position = vec_object[i]->getTransform().getLocalPosition();
		tmp_position = CoordConverter::cartesianToCylinder(tmp_position);

		//移動
		tmp_position.x = radius;	// xは円筒半径で固定
		tmp_position.y += radRotateSpeed * deltaTime;
		tmp_position.z += speedZ * deltaTime;	// zは指定スピードで進む - 敵一体

		//円筒座標をデカルト座標に変換
		Vec3 cartCoord = CoordConverter::cylinderToCartesian(tmp_position);

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
	swingCnt += deltaTime;
}

void PhalanxEnemy::init(Vec3 position, int length, int mainUnit, float radius, float speedZ)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	// 配列の再構築
	vec_object.resize(length);

	// 敵生成
	for (int i = 0; i < length; i++)
	{
		// 生成
		vec_object[i] = ModelGameObjectHelper::instantiateModel<int>(getUser().getGameMediator(), pCube);

		vec_object[i]->getTransform().setLocalPosition(position + Vec3(0, 0, i));
		vec_object[i]->addComponent<TestEnemy>()->init(0.0f, 0.0f);

		//弱点を強調表示
		if (i == mainUnit)
		{
			vec_object[i]->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		}
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
