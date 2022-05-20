#include "PlayerAttack.h"
#include "Actor/Base/GameObject.h"

#include "Component/Audio/AudioSource.h"
#include "Component/Graphics/Camera.h"

#include "Component/Physics/BoxColliderBt.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

#include "Device/GameDevice.h"

#include "Component/Follow/Follow.h"
#include "Component/Player/PlayerStats.h"
#include "Component/Player/PlayerParamManager.h"

#include "Device/GameInput.h"
#include "Device/ControllerInput.h"

#include "Effect/TestVibrationEffect.h"

#include "Utility/JsonFileManager.h"

#include "btBulletDynamicsCommon.h"

void PlayerAttack::onStart()
{
	//自身にコライダーをアタッチ
	m_pBoxCollider = getUser().addComponent<BoxColiiderBt>();
	m_pBoxCollider->setMass(1.0f);
	m_pBoxCollider->setTrigger(true);
	m_pBoxCollider->setUseGravity(false);
	m_pBoxCollider->setActive(false);

	//カメラがアタッチされているオブジェクトを取得
	auto pCameraObject = &getUser().getGameMediator()->getMainCamera()->getUser();

	//ActionManagerを取得
	m_pCameraActionManager = pCameraObject->getComponent<Action::ActionManager>();

	//AudioSourceをアタッチ
	m_pAudioSource = getUser().addComponent<AudioSource>();
	m_pAudioSource->setAudio("EnemyHit");
	m_pAudioSource->setVolume(0.1f);

	//プレイヤーに追従する
	auto pAttackFollow = getUser().addComponent<Follow>();
	pAttackFollow->SetGameObject(m_pModelTransform->getUser().getParent());
	pAttackFollow->Setdistance(Vec3(0.0f, 0.0f, 1.0f));

	//モデルにActionManagerアタッチ
	m_pModelActionManager = m_pModelTransform->getUser().addComponent<Action::ActionManager>();

	m_SlidingTimer.setMaxTime(1.5f);
}

void PlayerAttack::onUpdate()
{
	//入力を取得
	auto& gameInput = GameInput::getInstance();
	auto& controllerInput = ControllerInput::getInstance();

	//入力されていたら
	if (controllerInput.isPadButtonDown(ControllerInput::PAD_BUTTON::X) &&
		gameInput.getPlayerDash() &&
		m_SlidingTimer.isTime())
	{
		//スケールを縮める&その分移動
		m_pModelActionManager->enqueueAction(
			new Action::Spawn(
				{
					//ちょっとジャンプする
					new Action::Sequence(
						{
							new Action::EaseOutQuart(new Action::MoveTo(Vec3(1.0f, 0.0f, 0.0f), 0.25f)),
							new Action::EaseInQuart(new Action::MoveTo(Vec3(-0.25f, 0.0f, 0.0f), 0.4f))
						}
					),
				//スケールを縮める
				new Action::EaseInBack(new Action::ScaleTo(Vec3(0.5f, 0.8f, 0.9f), 0.35f)),
				//前転する
				new Action::EaseOutSine(new Action::RotateBy(Vec3(0.0f, -380.0f, 0.0f), 0.5f))
				}
			)
		);

		//コライダーを有効化
		m_pBoxCollider->setActive(true);
		m_SlidingTimer.reset();
	}

	m_SlidingTimer.update();

	if (m_SlidingTimer.isTime() ||
		m_pPlayerParam->isFuelZero())
	{
		//座標、スケール、回転を元に戻す
		m_pModelTransform->setLocalPosition(Vec3(0.0f, 0.0f, 0.0f));
		m_pModelTransform->setLocalScale(Vec3(1.0f));
		m_pModelTransform->setLocalAngles(Vec3::zero());

		//コライダーを無効化
		if (m_pBoxCollider->isActive())
			m_pBoxCollider->setActive(false);
	}
}

void PlayerAttack::init(Transform* pModelTransform, PlayerParamManager* pPlayerParam)
{
	m_pModelTransform = pModelTransform;
	m_pPlayerParam = pPlayerParam;
}

void PlayerAttack::onTriggerEnter(GameObject* pHit)
{
	//敵でないならreturn
	if (!pHit->compareTag("Enemy"))
		return;

	if (m_pCameraActionManager->actionCount() == 0)
		//カメラを揺らす
		m_pCameraActionManager->enqueueAction(new Action::TestVibrationEffect(m_pCameraActionManager));

	//エネミーの被ダメージ音を鳴らす
	m_pAudioSource->play();
}
