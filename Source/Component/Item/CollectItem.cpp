#include "CollectItem.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>
#include "Device/GameInput.h"
#include "CollectItemUI.h"

void CollectItem::onStart()
{
	// コライダー付与
	auto collider = getUser().addComponent<BoxColiiderBt>();
	collider->setTrigger(true);
	// 重力の無効化
	collider->setUseGravity(false);
	isDead = false;
}

void CollectItem::onUpdate()
{
	if (IsDead())
	{
		SetDead(false);
		getUser().destroy();
	}
}

void CollectItem::onTriggerEnter(GameObject* pHit)
{
	CollectItemUI::AddCount(CollectItemUI::GetCount());
	SetDead(true);
}