#include "DistanceActivater.h"

void DistanceActivater::onUpdate()
{
	if (player->getTransform().getLocalPosition().z > activationPos)
	{
		pObj->setActive(true);
	}
}
