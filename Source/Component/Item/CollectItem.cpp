#include "CollectItem.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>
#include "Device/GameInput.h"
#include "CollectItemUI.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Effect/CollectItemEffect.h"

void CollectItem::onStart()
{
	auto collider = getUser().addComponent<BoxColiiderBt>();
	collider->setTrigger(true);
	
	collider->setUseGravity(false);
	GameObj = new GameObject(getUser().getGameMediator());
	CollectItemUIObj = GameObj->addComponent<CollectItemUI>();
	m_pActionManager = getUser().addComponent<Action::ActionManager>();
}

void CollectItem::onUpdate()
{
	if (CollectItemUIObj->IsDead())
	{
		getUser().destroy();
	}
	else if (!CollectItemUIObj->IsDead())
	{
		if (m_pActionManager->actionCount() == 0)
		{
			//間隔を開けて火炎エフェクト
			auto pSequence = new Action::Sequence(
				{
					new Action::CollectItemEffect(m_pActionManager),
				}
			);

			//リピート実行
			auto pRepeat = new Action::RepeatForever(pSequence);

			m_pActionManager->enqueueAction(pRepeat);
		}
		else
		{
			//エフェクト停止
			if (m_pActionManager->actionCount() == 1)
				m_pActionManager->forceNext();
		}
	}
}

void CollectItem::onTriggerEnter(GameObject* pHit)
{
	if (CollectItemUI::GetCount() <= 1)
	{
		CollectItemUI::AddCount(CollectItemUI::GetCount());
	}
	CollectItemUIObj->SetDead(true);
}