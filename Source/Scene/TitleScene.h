#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/SceneEffect.h"
class TitleScene
	: public AbstractScene
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
	GameObject* titleObject = nullptr;
	GUISpriteRenderer* titleSprite = nullptr;
	GameObject* titleBGObject = nullptr;
	GUISpriteRenderer* titleBGSprite = nullptr;
	GameObject* fireObjects[100];
	GUISpriteRenderer* fireSprites[100];

	int life[100];
	int currentLife[100];
	float velocity[100];
	GameObject* pSceneEffect;
	SceneEffect* m_pSceneEffect;
	//シーン遷移エフェクトが終わったかどうか
	bool sceneEffectIsEnd;
};