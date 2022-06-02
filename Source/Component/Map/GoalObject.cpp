#include "Component/Map/GoalObject.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
void GoalObject::onStart()
{

}

void GoalObject::onUpdate()
{
	if (pPlayer->getTransform().getLocalPosition().z > goalObj->getTransform().getLocalPosition().z)
	{
		GameDevice::getGameTime().m_TimeScale = 0;
		GameInput::getInstance().setLock(true);
	}
}

void GoalObject::Initialize(float Zpos,GameObject* player)
{
	goalObj = new GameObject(getUser().getGameMediator());
	goalObj->getTransform().setLocalPosition(Vec3(0, 0, Zpos));
	pPlayer = player;
}
