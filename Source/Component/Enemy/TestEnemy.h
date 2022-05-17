#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"

class TestEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent ����Čp��
	virtual void onStart() override;
	virtual void onUpdate() override;

public:

	void init(float angle, float speed = 1.0f, float radius = 11.0f, Vec3 centerPoint = Vec3(0, 0, 0));

	void setCenter(Vec3 centerPoint) { this->centerPoint = centerPoint; }

	void setRadius(float radius) { this->rasius = radius; }

	/// <summary>
	/// �ړ������w��
	/// </summary>
	/// <param name="angle">�p�x(��)</param>
	void setVecAngle(float angle) { this->angle = angle; }

	/// <summary>
	/// �ړ������擾
	/// </summary>
	/// <returns>�p�x(��)</returns>
	float getVecAngle() { return angle; }

	/// <summary>
	/// ���x�Z�b�g
	/// </summary>
	/// <param name="speed">���x</param>
	void setSpeed(float speed) { this->speed = speed; }

	/// <summary>
	/// ���x�擾
	/// </summary>
	/// <returns>���x</returns>
	float getspeed() { return speed; }

private:
	// �̃f�[�^
	float angle = 0;
	Vec3 position{};
	float speed = 1.0f;
	Vec3 moveVec{};

	// �X�e�[�W���
	float rasius = 0;
	Vec3 centerPoint = Vec3(0, 0, 0);
};
