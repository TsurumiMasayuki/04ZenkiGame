#pragma once
#include <vector>
#include "Component/Base/AbstractComponent.h"

class TestEnemy;
class BoxColiiderBt;

namespace Action
{
	class ActionManager;
}

class PlayerSideAttack
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual void onTriggerEnter(GameObject* pHit) override;

	void startAttack();
	void endAttack();

private:
	void cameraCutIn();

private:
	BoxColiiderBt* m_pBoxCollider;
	Action::ActionManager* m_pActionManager;
	std::vector<GameObject*> m_MarkedEnemyList;
};