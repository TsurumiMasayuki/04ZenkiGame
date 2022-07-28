#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/TimeLimitUi.h"

class CheckPoint :
    public AbstractComponent
{
public:
	// AbstractComponent ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onStart() override;
	virtual void onUpdate() override;
	static bool  SetDead(bool flag) { return isDead = flag; }

	bool& IsDead() { return isDead; }

private:
	GameObject* GameObj;
	TimeLimitUi* timeLimit;
	static bool isDead;
	FLOAT128 checkPointScore;
	Vec3 reStartPos;
};

