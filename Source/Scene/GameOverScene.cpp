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
	//�I�u�W�F�N�g����
	gameOverObject = new GameObject(this);
	gameOverSprite = gameOverObject->addComponent<GUISpriteRenderer>();
	gameOverSprite->setTextureByName("erase");
	gameOverSprite->getTransform().setLocalPosition(Vec3{ 0,-50,3 });
	gameOverSprite->getTransform().setLocalScale(Vec3{ 900,600,1 });
	gameOverSprite->setActive(true);

	//Sound
	pAudio->setAudio("GameOver");
	pAudio->play(255);
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
