#include "LerpFollow.h"
#include "Device/GameDevice.h"

void LerpFollow::onStart()
{
	const auto& rotation = pObj->getTransform().getRotationMatrix();
	Vec3 rotateDistance = distance.multMatrix(rotation);

	const Vec3& basePosition = pObj->getTransform().getLocalPosition();
	getTransform().setLocalPosition(basePosition + rotateDistance);
}

void LerpFollow::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	const auto& rotation = pObj->getTransform().getRotationMatrix();
	Vec3 rotateDistance = distance.multMatrix(rotation);

	const Vec3& position = getTransform().getLocalPosition();
	const Vec3& basePosition = pObj->getTransform().getLocalPosition();
	getTransform().setLocalPosition(Vec3::lerp(position, basePosition + rotateDistance, deltaTime * 10.0f));

	float zAngle = pObj->getTransform().getLocalAngleZ();
	getTransform().setLocalAngleZ(zAngle - 90.0f);
}