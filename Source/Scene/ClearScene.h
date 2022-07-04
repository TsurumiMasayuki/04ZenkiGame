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

	//シーン遷移
	//開始
	GameObject* pSceneStartEffect;
	SceneEffect* m_pSceneStartEffect;
	//シーン開始エフェクトが終わったかどうか
	bool sceneStartEffectIsEnd;
	//終了
	GameObject* pSceneEndEffect;
	SceneEffect* m_pSceneEndEffect;
	//シーン終了エフェクトが終わったかどうか
	bool sceneEffectIsEnd;
	AudioSource* pAudio;
};