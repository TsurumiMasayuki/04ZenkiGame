#include "Follow.h"
#include "Device/GameDevice.h"

void Follow::onStart()
{
	//‰Šú‰»
	position = Vec3(0, 0, 0);
	distance = Vec3(0, 0, 0);
}

void Follow::onUpdate()
{
	position = distance + pObj->getTransform().getLocalPosition();
}
