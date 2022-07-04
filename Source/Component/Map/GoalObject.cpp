#include "Component/Map/GoalObject.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
#include "Utility/ModelGameObjectHelper.h"
void GoalObject::onStart()
{
	goalObj = new GameObject(getUser().getGameMediator());
	goalObj->getTransform().setLocalPosition(Vec3{ 0, 0, 100 });
	goalObj->getTransform().setLocalScale(Vec3{ 1280,720,1 });
	goalObjSprite =goalObj->addComponent<GUISpriteRenderer>();
	goalObjSprite->setTextureByName("goal");
	goalObjSprite->setActive(false);

	//Sound�֘A
	pAudio = goalObj->addComponent<AudioSource>();
	pAudio->setAudio("ClearJG");

  isGoal = false;
}

void GoalObject::onUpdate()
{
	if (goal->getTransform().getLocalPosition().distance(pPlayer->getTransform().getLocalPosition())<GOAL_DISTANCE)
	{
		//Sound�Đ�
		pAudio->play();

		GameDevice::getGameTime().m_TimeScale = 0;
		GameInput::getInstance().setLock(true);
	/*	goalObjSprite->setActive(true);*/
		isGoal = true;
	}
}

void GoalObject::Initialize(Vec3 goalPos,GameObject* player)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");
	goal = ModelGameObjectHelper::instantiateModel<int>(getUser().getGameMediator(),pCube);
	goal->getTransform().setLocalPosition(goalPos);

	pPlayer = player;
}

bool GoalObject::GetIsGoal()
{
	return isGoal;
}
