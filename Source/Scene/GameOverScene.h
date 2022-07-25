#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Component/Audio/AudioSource.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/SceneEffect.h"

class GameOverScene :
    public AbstractScene
{
public:
	virtual std::string nextScene() override;
	virtual bool isEnd() override;
	virtual void start() override;
	virtual void update() override;
	virtual void shutdown() override;

	void SubMove();
	void MainMove();
	void RePosition(int num);
private:
	GameObject* gameOverObject = nullptr;
	GUISpriteRenderer* gameOverSprite = nullptr;
	GameObject* gameOverBGObject = nullptr;
	GUISpriteRenderer* gameOverBGSprite = nullptr;
	GameObject* fireObjects[100];
	GUISpriteRenderer* fireSprites[100];
	GameObject* gameOverSelectObject = nullptr;
	GUISpriteRenderer* gameOverSelectSprite = nullptr;
	Vec3 SelectOnPos;
	Vec3 SelectOffPos;
	AudioSource* pAudio;
	bool isSelectToTitle;

	int life[100];
	int currentLife[100];
	float velocity[100];
	GameObject* pSceneEffect;
	SceneEffect* m_pSceneEffect;
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
};