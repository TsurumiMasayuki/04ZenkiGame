#include "PlayerDamage.h"
#include "Actor/Base/GameObject.h"
#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerParamManager.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Effect/TestPlayerAttackedEffect.h"

void PlayerDamage::onStart()
{
	m_MoveLockTimer.setMaxTime(1.5f);
}

void PlayerDamage::onUpdate()
{
	if (m_MoveLock)
	{
		m_MoveLockTimer.update();
		if (m_MoveLockTimer.isTime())
		{
			m_MoveLock = false;
			m_pPlayerParamManager->lockPlayerMove(false);
		}
	}
		
}

void PlayerDamage::init(PlayerAttack* pPlayerAttack, PlayerParamManager* pPlayerParamManager)
{
	m_pPlayerAttack = pPlayerAttack;
	m_pPlayerParamManager = pPlayerParamManager;
}

void PlayerDamage::onCollisionEnter(GameObject* pHit)
{
	if (!pHit->compareTag("Enemy")) 
		return;

	//攻撃中ならダメージを受けない
	if (m_pPlayerAttack->isAttacking())
		return;

	//ダメージを受ける
	m_pPlayerParamManager->onDamage();
	m_pPlayerParamManager->lockPlayerMove(true);
	m_pPlayerParamManager->setMoveSpeed(2.0f);
	m_pPlayerParamManager->setMoveDir(Vec3::zero());

	auto pParam = m_pPlayerParamManager;

	auto pAction = getUser().getComponent<Action::ActionManager>();

	if (pAction->actionCount() != 0) return;

	pAction->enqueueAction(new Action::TestPlayerAttackedEffect(nullptr));

	m_MoveLock = true;
	m_MoveLockTimer.reset();
}
