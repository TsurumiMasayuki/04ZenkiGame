#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

class PlayerAttack;
class PlayerParamManager;

class PlayerDamage
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void init(PlayerAttack* pPlayerAttack, PlayerParamManager* pPlayerParamManager);

	virtual void onCollisionEnter(GameObject* pHit) override;

private:
	PlayerAttack* m_pPlayerAttack;
	PlayerParamManager* m_pPlayerParamManager;

	bool m_MoveLock;
	Timer m_MoveLockTimer;
};