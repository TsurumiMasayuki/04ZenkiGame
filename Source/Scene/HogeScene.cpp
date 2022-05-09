#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/LinearlyEnemy.h"

#include "Component/Player/PlayerMovement.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Map/Map.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

std::string HogeScene::nextScene()
{
	return std::string();
}

bool HogeScene::isEnd()
{
	return false;
}

void HogeScene::start()
{
	auto& cameraTransform = getMainCamera()->getUser().getTransform();
	cameraTransform.setLocalPosition(Vec3(15.0f, 8.0f, 0.0f));
	cameraTransform.setLocalAngles(Vec3(45.0f, 0.0f, 0.0f));

	getMainCamera()->getUser().addComponent<Action::ActionManager>();
	getMainCamera()->getUser().addComponent<PlayerMovement>();

	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);

	pPlayer->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	pPlayer->getTransform().setLocalPosition(Vec3(15.0f, 1.0f, 7.0f));
	pPlayer->addComponent<PlayerMovement>();

	auto pEnemy = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	pEnemy->setTag("Enemy");
	pEnemy->getTransform().setLocalPosition(Vec3(10.0f, 0.0f, 10.0f));

	auto pBoxCollider = pEnemy->addComponent<BoxColiiderBt>();
	pBoxCollider->setMass(1.0f);
	pBoxCollider->setTrigger(false);
	pBoxCollider->setUseGravity(false);

	auto pTestEnemy = pEnemy->addComponent<TestEnemy>();
	pTestEnemy->SetTarget(pPlayer);

	//Map map;
	//map.Initialize(1, this);
	//map.CreateMap();
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}