#pragma once
#include "Component/Base/AbstractComponent.h"

class PlayerDamage
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual void onCollisionEnter(GameObject* pHit) override;
};