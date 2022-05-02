#pragma once
#include "Component/Base/AbstractComponent.h"

#include "Utility/Timer.h"

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
	//�ړ�
	void move(const Vec3& moveDir);

	//�_�b�V��
	void dash(const Vec3& moveDir);

private:
	Action::ActionManager* m_pActionManager;

	float m_BaseDashSpeed;
	float m_DashElapsedTime;
	float m_DashMaxTime;
};