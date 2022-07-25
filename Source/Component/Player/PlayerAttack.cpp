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
#include "Component/Player/PlayerSideAttack.h"

#include "Device/GameInput.h"
#include "Device/ControllerInput.h"

#include "Effect/TestVibrationEffect.h"
#include "Effect/HitStop.h"

#include "Utility/JsonFileManager.h"

#include "btBulletDynamicsCommon.h"

void PlayerAttack::onStart()
{
	//カメラがアタッチされているオブジェクトを取得
	auto pCameraObject = &getUser().getGameMediator()->getMainCamera()->getUser();

	//ActionManagerを取得
	m_pCameraActionManager = pCameraObject->getComponent<Action::ActionManager>();

	//AudioSourceをアタッチ
	m_pAudioSource = getUser().addComponent<AudioSource>();
	m_pAudioSource->setAudio("HitEnemy");
	m_pAudioSource->setVolume(0.1f);


	m_SlidingTimer.setMaxTime(1.5f);

	auto pRightSideObject = new GameObject(getUser().getGameMediator());
	m_pRightSideAttack = pRightSideObject->addComponent<PlayerSideAttack>();
	auto pRightFollow = pRightSideObject->addComponent<Follow>();
	pRightFollow->SetGameObject(&getUser());
	pRightFollow->Setdistance(Vec3(1.0f, 0.0f, 0.0f));

	auto pLeftSideObject = new GameObject(getUser().getGameMediator());
	m_pLeftSideAttack = pLeftSideObject->addComponent<PlayerSideAttack>();
	auto pLeftFollow = pLeftSideObject->addComponent<Follow>();
	pLeftFollow->SetGameObject(&getUser());
	pLeftFollow->Setdistance(Vec3(-1.0f, 0.0f, 0.0f));
}

void PlayerAttack::onUpdate()
{
	//入力を取得
	auto& gameInput = GameInput::getInstance();

	//入力されていたら
	if (gameInput.getSliding() &&
		m_SlidingTimer.isTime())
	{
		//回転する
		m_pModelActionManager->enqueueAction(
			new Action::RepeatForever(new Action::EaseOutSine(new Action::RotateBy(Vec3(0.0f, -360.0f, 0.0f), 0.5f)))
		);

		m_SlidingTimer.reset();

		m_pRightSideAttack->startAttack();
		m_pLeftSideAttack->startAttack();
	}

	m_SlidingTimer.update();

	if ((m_SlidingTimer.isTime() ||
		m_pPlayerParam->isFuelZero()))
	{
		//座標、スケール、回転を元に戻す
		m_pModelTransform->setLocalPosition(m_OriginModelPosition);
		m_pModelTransform->setLocalScale(m_OriginModelScale);
		m_pModelTransform->setLocalAngles(m_OriginModelAngles);

		//回転終了
		m_pModelActionManager->forceNext();

		m_pRightSideAttack->endAttack();
		m_pLeftSideAttack->endAttack();
	}
}

bool PlayerAttack::isAttacking()
{
	return !m_SlidingTimer.isTime();
}

void PlayerAttack::init(Transform* pModelTransform, PlayerParamManager* pPlayerParam)
{
	m_pPlayerParam = pPlayerParam;

	m_pModelTransform = pModelTransform;
	m_OriginModelPosition = m_pModelTransform->getLocalPosition();
	m_OriginModelScale = m_pModelTransform->getLocalScale();
	m_OriginModelAngles = m_pModelTransform->getLocalAngles();

	//ActionManagerをアタッチ
	m_pModelActionManager = m_pModelTransform->getUser().addComponent<Action::ActionManager>();
}

void PlayerAttack::onCollisionEnter(GameObject* pHit)
{
	//スライディング中でないならreturn
	if (!isAttacking()) 
		return;

	//敵でないならreturn
	if (!pHit->compareTag("Enemy"))
		return;

	//撃破時加速
	m_pPlayerParam->setHitEnemy();
	m_pPlayerParam->attackStockAddition();

	if (m_pCameraActionManager->actionCount() == 0)
		//カメラを揺らす
		m_pCameraActionManager->enqueueAction(new Action::TestVibrationEffect(m_pCameraActionManager));

	//エネミーの被ダメージ音を鳴らす
	m_pAudioSource->play();

	//敵にAction設定
	auto pActionManager = pHit->addComponent<Action::ActionManager>();

	auto& random = GameDevice::getRandom();

	float x = random.getRandom(-5.0f, 5.0f);
	float z = random.getRandom(-5.0f, 5.0f);

	auto pSpawn = new Action::Spawn(
		{
			new Action::Sequence(
				{
					new Action::EaseOutBack(
						new Action::MoveBy(
							Vec3(x, 3.0f, z),
						0.6f)),
					new Action::EaseInCirc(
						new Action::MoveBy(
						Vec3(x, -15.0f, z),
						1.0f))
				}
			),
			new Action::RotateBy(
				Vec3(0.0f, 0.0f, 480.0f), 1.6f
			)
		}
	);

	//飛ばす
	pActionManager->enqueueAction(pSpawn);

	HitStop::getInstance().Start(0.1f, 1.0f);
}
