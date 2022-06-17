#include "SlidingThrough.h"
#include "Actor/Base/GameObject.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
#include "Device/ControllerInput.h"
#include "Utility/ModelGameObjectHelper.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"
#include "Component/Physics/BoxColliderBt.h"
#include "btBulletDynamicsCommon.h"

void SlidingThrough::onStart()
{
	auto pCollider = getUser().addComponent<BoxColiiderBt>();
	pCollider->setMass(0.0f);
	pCollider->setUseGravity(false);
	pCollider->setTrigger(false);

	o_Timer.setMaxTime(1.0f);
}

void SlidingThrough::onUpdate()
{
	o_Timer.update();
	//入力を取得
	auto& gameInput = GameInput::getInstance();
	
	if (gameInput.getPlayerDash() && gameInput.getSliding() && o_Timer.isTime())
	{
		o_Timer.reset();
		 //当たり判定のON
		getUser().getComponent<BoxColiiderBt>()->setActive(false);
    }

	if (o_Timer.isTime())
	{
		//コライダーを無効化
		if (getUser().getComponent<BoxColiiderBt>()->isActive() == false)
			getUser().getComponent<BoxColiiderBt>()->setActive(true);
	}
}

void SlidingThrough::onTriggerEnter(GameObject* pHit)
{

}
