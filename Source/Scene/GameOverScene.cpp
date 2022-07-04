#include "GameOverScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/D2DTextRenderer.h"
#include "Device/GameDevice.h"
#include "Device/ControllerInput.h"

std::string GameOverScene::nextScene()
{
	return "Title";
}

bool GameOverScene::isEnd()
{
	return GameDevice::getInput().isKeyDown(DIK_SPACE) ||
		ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START);
}

void GameOverScene::start()
{
	//オブジェクト生成
	gameOverObject = new GameObject(this);
	gameOverSprite = gameOverObject->addComponent<GUISpriteRenderer>();
	gameOverSprite->setTextureByName("gameOver");
	gameOverSprite->getTransform().setLocalPosition(Vec3{ 0,0,1 });
	gameOverSprite->getTransform().setLocalScale(Vec3{ 1280,720,1 });
	gameOverSprite->setActive(true);
}

void GameOverScene::update()
{
}

void GameOverScene::shutdown()
{
}

void GameOverScene::SubMove()
{
}

void GameOverScene::MainMove()
{
}

void GameOverScene::RePosition(int num)
{
}
