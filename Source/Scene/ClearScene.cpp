#include "ClearScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/D2DTextRenderer.h"
#include "Device/GameDevice.h"
#include "Device/ControllerInput.h"

std::string ClearScene::nextScene()
{
	return "Title";
}

bool ClearScene::isEnd()
{
	return GameDevice::getInput().isKeyDown(DIK_SPACE) ||
		ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START);
}

void ClearScene::start()
{
	ClearObject = new GameObject(this);
	ClearObject->getTransform().setLocalPosition(Vec3{ 0,0,1 });
	ClearObject->getTransform().setLocalScale(Vec3{ 700,600,1 });
	ClearSprite = ClearObject->addComponent<GUISpriteRenderer>();
	ClearSprite->setTextureByName("clear");
}

void ClearScene::update()
{

}

void ClearScene::shutdown()
{
}
