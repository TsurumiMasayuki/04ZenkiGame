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
	return m_pSceneEndEffect->IsEnd();
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

	//Sound
	pAudio->setAudio("GameOver");
	pAudio->play(255);
  
	// SceneEffectオブジェクト生成
	pSceneEndEffect = new GameObject(this);
	m_pSceneEndEffect = pSceneEndEffect->addComponent<SceneEffect>();
	m_pSceneEndEffect->Initialize(1);
	pSceneStartEffect = new GameObject(this);
	m_pSceneStartEffect = pSceneStartEffect->addComponent<SceneEffect>();
	m_pSceneStartEffect->Initialize(0);
	m_pSceneStartEffect->StartEffect();
}

void GameOverScene::update()
{
	if (m_pSceneStartEffect->IsEnd())
	{
		if (GameDevice::getInput().isKeyDown(DIK_SPACE) ||
			ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START))
		{
			m_pSceneEndEffect->StartEffect();
		}
	}
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
