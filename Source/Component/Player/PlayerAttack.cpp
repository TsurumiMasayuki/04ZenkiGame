#include "PlayerAttack.h"
#include "Actor/Base/GameObject.h"

#include "Component/Audio/AudioSource.h"
#include "Component/Graphics/Camera.h"

#include "Component/Physics/BoxColliderBt.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

#include "Component/Player/PlayerStats.h"

#include "Device/GameInput.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

#include "Utility/JsonFileManager.h"

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
}

void PlayerAttack::onUpdate()
{
	//入力を取得
	bool input = GameInput::getInstance().getPlayerDash();

	//入力されていたら
	if (input)
	{
		if (m_pPlayerActionManager->actionCount() == 0)
		{
			//間隔を開けて火炎エフェクト
			auto pSequence = new Action::Sequence(
				{
					new Action::TestFlameEffect(m_pPlayerActionManager),
					new Action::WaitForSeconds(0.5f)
				}
			);

			//リピート実行
			auto pRepeat = new Action::RepeatForever(pSequence);

			m_pPlayerActionManager->enqueueAction(pRepeat);
		}

		//コライダーを有効化
		m_pBoxCollider->setActive(true);
	}
	else
	{
		//エフェクトを停止
		m_pPlayerActionManager->forceNext();
		//コライダーを無効化
		m_pBoxCollider->setActive(false);
	}
}

void PlayerAttack::init(Action::ActionManager* pPlayerActionManager)
{
	m_pPlayerActionManager = pPlayerActionManager;
}

void PlayerAttack::onCollisionEnter(GameObject* pHit)
{
	//敵でないならreturn
	if (!pHit->compareTag("Enemy")) 
		return;

	if (m_pCameraActionManager->actionCount() > 0) 
		return;

	//カメラを揺らす
	m_pCameraActionManager->enqueueAction(new Action::TestVibrationEffect(m_pCameraActionManager));

	//エネミーの被ダメージ音を鳴らす
	m_pAudioSource->play();
}
