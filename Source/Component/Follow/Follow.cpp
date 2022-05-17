#include "Follow.h"
#include "Device/GameDevice.h"

void Follow::onStart()
{
}

void Follow::onUpdate()
{
	getTransform().setLocalPosition(pObj->getTransform().getLocalPosition() + distance);
}
