#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Base/AbstractComponent.h"
#include "Component/Audio/AudioSource.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/SceneEffect.h"
#include "Component/Graphics/SpriteRenderer.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Utility/Timer.h"

namespace Action
{
	class ActionManager;
}

struct ResultContents
{
	GameObject* resultClear;
	GameObject* resultCheckPoint[2];
	GameObject* resultComprehensive;
	GameObject* resultBar[3];
	GameObject* lapTimeObject[4][5][10];

	GUISpriteRenderer* resultClearSprite;
	GUISpriteRenderer* resultCheckPointSprite[2];
	GUISpriteRenderer* resultComprehensiveSprite;
	GUISpriteRenderer* resultBarSprite[3];
	GUISpriteRenderer* lapTimeSprite[4][5][10];
};

class ClearScene :public AbstractScene
{
public:

	virtual std::string nextScene() override;
	virtual bool isEnd() override;
	virtual void start() override;
	virtual void update() override;
	virtual void shutdown() override;

	void SetSprite(GUISpriteRenderer* sprite[3][5][10]);

	void ActiveLaptime();

	void SpriteEasing();
private:
	GameObject* ClearObject;
	GameObject* resultBack;

	ResultContents resultContents;
	SpriteRenderer* ClearSprite;
	SpriteRenderer* resultBackSprite;
	AudioSource* pAudio;

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
};