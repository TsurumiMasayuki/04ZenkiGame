#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

namespace Action
{
	class ActionManager;
}

class AudioSource;

//プレイヤーの攻撃用コンポーネント
class PlayerAttack
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

protected:
	virtual void onCollisionEnter(GameObject* pHit) override;

private:
	//プレイヤーモデルにアタッチされているActionManager
	Action::ActionManager* m_pModelActionManager;

	//カメラにアタッチされているActionManager
	Action::ActionManager* m_pCameraActionManager;

	//ダメージ用音声
	AudioSource* m_pAudioSource;
};