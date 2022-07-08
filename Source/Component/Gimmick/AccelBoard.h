#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class AccelBoad
	: AbstractComponent
{
public:
	// AbstractComponent ����Čp������܂���
	virtual void onStart() override;
	virtual void onUpdate() override;

	void setTarget(GameObject* object) { targetObj = object; }

	/// <summary>
	/// �����x�ݒ�
	/// </summary>
	/// <param name="acceleration"></param>
	void setAcceleration(float acceleration) { this->acceleration = acceleration; }

private:
	GameObject* targetObj = nullptr;

	Vec3 scale{};

	bool isExpansion = false;
	
	float acceleration = 1.3f;

	bool interval = true;
	Timer activeTimer;
};