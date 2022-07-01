#include "PlayerDamage.h"
#include "Actor/Base/GameObject.h"
#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerParamManager.h"

#include "Component/Utility/Action/ActionManager.h"
#include "Effect/TestPlayerAttackedEffect.h"

void PlayerDamage::onStart()
{
}

void PlayerDamage::onUpdate()
{
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

	getUser().getComponent<Action::ActionManager>()->enqueueAction(new Action::TestPlayerAttackedEffect(nullptr));
}
