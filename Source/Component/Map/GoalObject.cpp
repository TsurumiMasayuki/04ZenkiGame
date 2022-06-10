#include "Component/Map/GoalObject.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
void GoalObject::onStart()
{
	goalObj = new GameObject(getUser().getGameMediator());
	goalObj->getTransform().setLocalPosition(Vec3{ 0, 0, 100 });
	goalObj->getTransform().setLocalScale(Vec3{ 1280,720,1 });
	goalObjSprite =goalObj->addComponent<GUISpriteRenderer>();
	goalObjSprite->setTextureByName("goal");
	goalObjSprite->setActive(false);
}

void GoalObject::onUpdate()
{
	if (m_pPlayer->getTransform().getLocalPosition().z >goalPos->getTransform().getLocalPosition().z)
	{
		GameDevice::getGameTime().m_TimeScale = 0;
		GameInput::getInstance().setLock(true);
		goalObjSprite->setActive(true);
	}
}

void GoalObject::Initialize(float Zpos,GameObject* player)
{
	goalPos = new GameObject(getUser().getGameMediator());
	goalPos->getTransform().setLocalPosition(Vec3(0, 0, Zpos));
	m_pPlayer = player;
}
