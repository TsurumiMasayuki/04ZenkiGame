#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class Zigzagenemy
	: AbstractComponent
{
public:
	// AbstractComponent ����Čp������܂���
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="speedY">���ړ���</param>
	/// <param name="speedZ">���ړ���</param>
	/// <param name="radius">�~�����a</param>
	void init(Vec3 position, float speedY, float speedZ, float radius = 11.0f);

	/// <summary>
	/// �܂�Ԃ�
	/// </summary>
	void wrap();

private:
	Vec3 position{};
	Vec3 velocity{};
	float radius = 0;

	int dir = false;

	Timer wrapTimer;
};