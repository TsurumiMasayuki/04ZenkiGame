#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
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
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}