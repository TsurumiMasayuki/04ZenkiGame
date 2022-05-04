#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Player/PlayerMovement.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Effect/TestEffect.h"
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
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	pPlayer->getTransform().setLocalPosition(Vec3(0.0f, -10.0f, 10.0f));
	pPlayer->getTransform().setLocalScale(Vec3(0.02f, 0.02f, 0.02f));
	pPlayer->addComponent<PlayerMovement>();
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}