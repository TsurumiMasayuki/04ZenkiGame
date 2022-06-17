#include "CollectItem.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void CollectItem::onStart()
{
	// コライダー付与
	auto collider = getUser().addComponent<BoxColiiderBt>();
	collider->setTrigger(true);
	// 重力の無効化
	collider->setUseGravity(false);
	isDead = false;
	count = 1;

	itemObj = new GameObject(getUser().getGameMediator());
	GUISpriteRenderer* itemSprite = itemObj->addComponent<GUISpriteRenderer>();
	itemSprite->setTextureByName("collectItemF");
	if (!GetDead())
	{
		itemObj->getTransform().setLocalPosition(Vec3{ 300,330,1 });
		itemObj->getTransform().setLocalScale(Vec3{ 64 });
	}
}

void CollectItem::onUpdate()
{

}

void CollectItem::onTriggerEnter(GameObject* pHit)
{
	if (!GetDead())
	{
		getUser().destroy();
		SetDead(true);
	}


	//itemObj->getTransform().setLocalPosition(Vec3{ 300,330,0 });
	//itemObj->getTransform().setLocalScale(Vec3{ 0 });
}