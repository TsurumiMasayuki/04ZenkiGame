#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class BoundGimmick
	: AbstractComponent
{
public:
	// AbstractComponent ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onStart() override;
	virtual void onUpdate() override;

	void setTarget(GameObject* object) { targetObj = object; }

private:
	GameObject* targetObj = nullptr;

	Vec3 scale{};

	bool isExpansion = false;
	Timer changeTime;
};