#include "CheckPoint.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/TestUI/TimeLimitUi.h"
#include "Component/TestUI/LapTime.h"

bool CheckPoint::isDead = false;

void CheckPoint::onStart()
{
	auto collider = getUser().addComponent<BoxColiiderBt>();
	collider->setTrigger(true);
	collider->setUseGravity(false);
	collider->setMass(1.0f);

	// 敵としてタグ付け
	getUser().setTag("CheckPoint");
}

void CheckPoint::onUpdate()
{
	if (IsDead())
	{
		getUser().destroy();
		SetDead(false);
	}
}
