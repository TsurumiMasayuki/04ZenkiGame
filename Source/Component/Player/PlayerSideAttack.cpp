#include "PlayerSideAttack.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

#include "Component/Follow/Follow.h"

#include "Effect/TestFlameEffect.h"

#include "btBulletDynamicsCommon.h"

void PlayerSideAttack::onStart()
{
	//自身にコライダーをアタッチ
	m_pBoxCollider = getUser().addComponent<BoxColiiderBt>();
	m_pBoxCollider->setMass(1.0f);
	m_pBoxCollider->setTrigger(true);
	m_pBoxCollider->setUseGravity(false);
	m_pBoxCollider->setActive(false);

	//ActionManagerをアタッチ
	m_pActionManager = getUser().addComponent<Action::ActionManager>();
}

void PlayerSideAttack::onUpdate()
{
}

void PlayerSideAttack::onTriggerEnter(GameObject* pHit)
{
	if (pHit->compareTag("Enemy"))
		m_MarkedEnemyList.emplace_back(pHit);
}

void PlayerSideAttack::startAttack()
{
	m_pBoxCollider->setActive(true);

	if (m_pActionManager->actionCount() == 0)
	{
		//間隔を開けて火炎エフェクト
		auto pSequence = new Action::Sequence(
			{
				new Action::TestFlameEffect(m_pActionManager),
				new Action::WaitForSeconds(0.1f)
			}
		);

		//リピート実行
		auto pRepeat = new Action::RepeatForever(pSequence);

		m_pActionManager->enqueueAction(pRepeat);
	}
}

void PlayerSideAttack::endAttack()
{
	return;

	m_pBoxCollider->setActive(false);

	//エフェクト停止
	if (m_pActionManager->actionCount() == 1)
		m_pActionManager->forceNext();

	for (GameObject* pEnemy : m_MarkedEnemyList)
	{
		//敵にAction設定
		auto pActionManager = pEnemy->addComponent<Action::ActionManager>();

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
	}

	//5体以上巻き込んだら
	if (m_MarkedEnemyList.size() >= 5)
	{
		cameraCutIn();
	}

	m_MarkedEnemyList.clear();
}

void PlayerSideAttack::cameraCutIn()
{
	//ActionManager取得
	auto pActionManager = getUser().getGameMediator()->getMainCamera()->getUser().getComponent<Action::ActionManager>();
	pActionManager->setUseUnscaledTime(true);

	auto& gameTime = GameDevice::getGameTime();
	gameTime.m_TimeScale = 0.1f;

	const float effectTime = 0.1f;

	auto pSpawn = new Action::Spawn(
		{
			new Action::EaseInCirc(
				new Action::MoveBy(Vec3(0.0f, 0.0f, -10.0f), effectTime)
			)
		}
	);

	pSpawn->setUseUnscaledTime(true);

	auto pSpawnReverse = new Action::Spawn(
		{
			new Action::EaseInCirc(
				new Action::MoveBy(Vec3(0.0f, 0.0f, 10.0f), effectTime)
			)
		}
	);

	pSpawnReverse->setUseUnscaledTime(true);

	//Action登録
	pActionManager->enqueueAction(pSpawn);

	pActionManager->enqueueAction(new Action::WaitForSeconds(1.0f));

	pActionManager->enqueueAction(pSpawnReverse);

	pActionManager->enqueueAction(
		new Action::CallFunc(
			[&gameTime, pActionManager]()
			{
				pActionManager->setUseUnscaledTime(false);
				gameTime.m_TimeScale = 1.0f;
			}
		)
	);
}
