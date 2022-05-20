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

	void init(float speed, float rotateSpeed, float radius = 11.0f, Vec3 centerPoint = Vec3(0, 0, 0));

	void setCenter(Vec3 centerPoint) { this->centerPoint = centerPoint; }

	void setRadius(float radius) { this->radius = radius; }

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
	//���x
	float speed;
	//��]���x
	float rotateSpeed;

	// �X�e�[�W���
	float radius = 0.0f;
	Vec3 centerPoint = Vec3(0, 0, 0);

	Vec3 m_CylinderCoord;
};
