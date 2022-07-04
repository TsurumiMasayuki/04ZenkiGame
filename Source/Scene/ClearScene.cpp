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
	return m_pSceneEndEffect->IsEnd();
}

void ClearScene::start()
{
	ClearObject = new GameObject(this);
	ClearObject->getTransform().setLocalPosition(Vec3{ 0,0,2 });
	ClearObject->getTransform().setLocalScale(Vec3{ 700,600,1 });
	ClearSprite = ClearObject->addComponent<GUISpriteRenderer>();
	ClearSprite->setTextureByName("clear");

	//SceneEffectオブジェクト生成
	pSceneEndEffect = new GameObject(this);
	m_pSceneEndEffect = pSceneEndEffect->addComponent<SceneEffect>();
	m_pSceneEndEffect->Initialize(1);
	pSceneStartEffect = new GameObject(this);
	m_pSceneStartEffect = pSceneStartEffect->addComponent<SceneEffect>();
	m_pSceneStartEffect->Initialize(0);
	m_pSceneStartEffect->StartEffect();

	//Sound
	pAudio->setAudio("Endeng");
	pAudio->play(255);
}

void ClearScene::update()
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

void ClearScene::shutdown()
{
}
