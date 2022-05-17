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

	void init(Transform* pModelTransform);

protected:
	virtual void onTriggerEnter(GameObject* pHit) override;

private:
	//自身にアタッチされたBoxCollider
	BoxColiiderBt* m_pBoxCollider;

	//プレイヤーのモデルの座標系
	Transform* m_pModelTransform;

	//カメラにアタッチされているActionManager
	Action::ActionManager* m_pCameraActionManager;

	//ダメージ用音声
	AudioSource* m_pAudioSource;
};