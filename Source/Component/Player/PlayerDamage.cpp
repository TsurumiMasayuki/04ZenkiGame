#include "PlayerDamage.h"
#include "Actor/Base/GameObject.h"

void PlayerDamage::onStart()
{
}

void PlayerDamage::onUpdate()
{
}

void PlayerDamage::onCollisionEnter(GameObject* pHit)
{
	if (!pHit->compareTag("Enemy")) 
		return;

	
}
