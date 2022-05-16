#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/LinearlyEnemy.h"

#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"

#include "Component/Map/Map.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Player/PlayerParamManager.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"
#include "Component/TestUI/TestUI.h"

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
	cameraTransform.setLocalPosition(Vec3(0.0f, 6.0f, 0.0f));
	cameraTransform.setLocalAngles(Vec3(10.0f, 0.0f, 0.0f));

	getMainCamera()->getUser().addComponent<Action::ActionManager>();

	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);

	pPlayer->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	pPlayer->getTransform().setLocalPosition(Vec3(0.0f, 0.0f, 3.0f));
	auto pPlayerParam = pPlayer->addComponent<PlayerParamManager>();
	auto pPlayerMove = pPlayer->addComponent<PlayerMovement>();

	pPlayerMove->init(pPlayerParam);
	pPlayerMove->setCylinderRadius(5.0f);
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}