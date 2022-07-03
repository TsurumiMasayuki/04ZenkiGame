#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class BarrierEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent ����Čp������܂���
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="position">�������W</param>
	/// <param name="speedZ">���ړ���</param>
	/// <param name="speedY">���ړ���</param>
	/// <param name="radius">�~�����a</param>
	void init(Vec3 position, float speedZ, float speedY, float radius = 11.0f);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="object"></param>
	void setTarget(GameObject* object) { targetObj = object; }

private:
	Vec3 position{};
	Vec3 velocity{};
	float radius = 0;

	GameObject* targetObj;

	Vec3 rotation{};
	float ratateSpeed = 0.0f;

};