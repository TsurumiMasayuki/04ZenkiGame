#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class BoundGimmick
	: public AbstractComponent
{
public:
	// AbstractComponent を介して継承されました
	virtual void onStart() override;
	virtual void onUpdate() override;

	void setTarget(GameObject* object) { targetObj = object; }

private:
	GameObject* targetObj = nullptr;

	Vec3 scale{};

	bool isExpansion = false;
	Timer changeTime;
};