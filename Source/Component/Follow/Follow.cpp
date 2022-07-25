#include "Follow.h"
#include "Device/GameDevice.h"

void Follow::onStart()
{
}

void Follow::onUpdate()
{
	const auto& rotation = pObj->getTransform().getRotationMatrix();
	Vec3 rotateDistance = distance.multMatrix(rotation);

	getTransform().setLocalPosition(pObj->getTransform().getLocalPosition() + rotateDistance);
	/*float zAngle = pObj->getTransform().getLocalAngleZ();
	getTransform().setLocalAngleZ(zAngle - 90.0f);*/
}
