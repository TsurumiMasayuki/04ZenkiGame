#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Base/AbstractComponent.h"
#include "Component/Audio/AudioSource.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/SceneEffect.h"
class ClearScene :public AbstractScene
{
public:

	virtual std::string nextScene() override;
	virtual bool isEnd() override;
	virtual void start() override;
	virtual void update() override;
	virtual void shutdown() override;
private:
	GameObject* ClearObject;
	GUISpriteRenderer* ClearSprite;

	//�V�[���J��
	//�J�n
	GameObject* pSceneStartEffect;
	SceneEffect* m_pSceneStartEffect;
	//�V�[���J�n�G�t�F�N�g���I��������ǂ���
	bool sceneStartEffectIsEnd;
	//�I��
	GameObject* pSceneEndEffect;
	SceneEffect* m_pSceneEndEffect;
	//�V�[���I���G�t�F�N�g���I��������ǂ���
	bool sceneEffectIsEnd;
	AudioSource* pAudio;
};