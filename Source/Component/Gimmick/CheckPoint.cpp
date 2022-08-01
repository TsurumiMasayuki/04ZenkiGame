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

	// �G�Ƃ��ă^�O�t��
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
