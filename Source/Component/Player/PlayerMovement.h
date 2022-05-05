#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

#include "Component/Player/PlayerStats.h"

namespace Action
{
	class ActionManager;
}

class PlayerMovement
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

private:
	//移動
	void move(const Vec3& moveDir);

	//ダッシュ
	void dash(const Vec3& moveDir);

private:
	Action::ActionManager* m_pActionManager;

	PlayerStats m_Stats;

	float m_DashElapsedTime;
	float m_DashMaxTime;
};