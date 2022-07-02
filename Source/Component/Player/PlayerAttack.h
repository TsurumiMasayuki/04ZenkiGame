#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

namespace Action
{
	class ActionManager;
}

class BoxColiiderBt;
class AudioSource;
class PlayerParamManager;
class PlayerSideAttack;

//プレイヤーの攻撃用コンポーネント
class PlayerAttack
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void init(Transform* pModelTransform, PlayerParamManager* pPlayerParam);

protected:
	virtual void onTriggerEnter(GameObject* pHit) override;

private:
	//自身にアタッチされたBoxCollider
	BoxColiiderBt* m_pBoxCollider;

	//プレイヤーのモデルの座標系
	Transform* m_pModelTransform;

	//モデルにアタッチされているActionManager
	Action::ActionManager* m_pModelActionManager;

	//カメラにアタッチされているActionManager
	Action::ActionManager* m_pCameraActionManager;

	//ダメージ用音声
	AudioSource* m_pAudioSource;

	//プレイヤーのパラメータ
	PlayerParamManager* m_pPlayerParam;

	//スライディングの時間
	Timer m_SlidingTimer;

	//右の攻撃判定
	PlayerSideAttack* m_pRightSideAttack;

	//左の攻撃判定
	PlayerSideAttack* m_pLeftSideAttack;

	Vec3 m_OriginModelPosition;
	Vec3 m_OriginModelScale;
	Vec3 m_OriginModelAngles;
};