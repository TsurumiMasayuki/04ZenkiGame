#include "DistanceActivater.h"

void DistanceActivater::onUpdate(GameObject* player)
{
	if (player->getTransform().getLocalPosition().z > activationPos)
	{
		pObj->setActive(true);
	}
}
