#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

namespace Action
{
	class ActionManager;
}

class BoxColiiderBt;
class AudioSource;

//プレイヤーの攻撃用コンポーネント
class PlayerAttack
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void init(Action::ActionManager* pPlayerActionManager);

protected:
	virtual void onCollisionEnter(GameObject* pHit) override;

private:
	//自身にアタッチされたBoxCollider
	BoxColiiderBt* m_pBoxCollider;

	//プレイヤーにアタッチされているActionManager
	Action::ActionManager* m_pPlayerActionManager;

	//カメラにアタッチされているActionManager
	Action::ActionManager* m_pCameraActionManager;

	//ダメージ用音声
	AudioSource* m_pAudioSource;
};