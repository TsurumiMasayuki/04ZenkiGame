#include "Component/Map/GoalObject.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
#include "Utility/ModelGameObjectHelper.h"
#include "Component/Player/PlayerParamManager.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include <Component/Follow/LerpFollow.h>

void GoalObject::onStart()
{
	goalObj = new GameObject(getUser().getGameMediator());
	goalObj->getTransform().setLocalPosition(Vec3{ 0, 0, 100 });
	goalObj->getTransform().setLocalScale(Vec3{ 1280,720,1 });
	goalObjSprite = goalObj->addComponent<GUISpriteRenderer>();
	goalObjSprite->setTextureByName("goal");
	goalObjSprite->setActive(false);
	velocity = 0.0f;
	//Sound�֘A
	pAudio = goalObj->addComponent<AudioSource>();
	pAudio->setAudio("ClearJG");

  isGoal = false;
  isSound = false;
}

void GoalObject::onUpdate()
{
	Vec3 pos = goal->getTransform().getLocalPosition();
	velocity = pPlayer->getComponent<PlayerParamManager>()->getMoveSpeed();
	for (int i = 0; i < 60; i++)
	{
		pos.z += velocity / 60;
		//if(isGoal==false)pAudio->play();

		if (pos.distance(pPlayer->getTransform().getLocalPosition()) < GOAL_DISTANCE && !isGoal)
		{
			if (isGoal && !isSound)
			{
				pAudio->play();
				isSound = true;
			}
			GameDevice::getGameTime().m_TimeScale = 0;
			GameInput::getInstance().setLock(true);
			/*	goalObjSprite->setActive(true);*/
			isGoal = true;

			Random& random = GameDevice::getRandom();

			getUser().getGameMediator()->getMainCamera()->getUser().getComponent<LerpFollow>()->Setdistance(Vec3(20.0f, 0.0f, 0.0f));

			for (auto goalEffect : goalEffects)
			{
				auto pAction = goalEffect->getUser().addComponent<Action::ActionManager>();
				pAction->setUseUnscaledTime(true);
				auto pMove = new Action::MoveBy(Vec3(random.getRandom(-10.0f, 10.0f), random.getRandom(-10.0f, 10.0f), random.getRandom(-1.0f, 10.0f) * velocity), 1.0f);
				pMove->setUseUnscaledTime(true);
				pAction->enqueueAction(new Action::EaseOutQuad(pMove));
			}
		}
	}

}

void GoalObject::Initialize(Vec3 goalPos, GameObject* player)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");
	goal = ModelGameObjectHelper::instantiateModel<int>(getUser().getGameMediator(), pCube);
	goal->getTransform().setLocalPosition(goalPos);

	pPlayer = player;

	const float scale = 0.5f;
	const int count = 12;

	for (int y = -count; y < count; y++)
	{
		for (int x = -count; x < count; x++)
		{
			auto pObj = ModelGameObjectHelper::instantiateModel<int>(getUser().getGameMediator(), GameDevice::getModelManager().getModel("Cube"));
			pObj->getTransform().setLocalPosition(goalPos + Vec3(x * scale, y * scale + 5.0f, 0.0f));
			pObj->getTransform().setLocalScale(Vec3(scale));

			goalEffects.emplace_back(&pObj->getTransform());
		}
	}
}

bool GoalObject::GetIsGoal()
{
	return isGoal;
}
