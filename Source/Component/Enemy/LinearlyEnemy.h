#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class LinearlyEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent ����Čp��
	virtual void onStart() override;
	virtual void onUpdate() override;

public:
	/// <summary>
	/// �ڕW�I�u�W�F�N�g�Z�b�g
	/// </summary>
	/// <param name="object">�ڕW�I�u�W�F�N�g</param>
	void SetTarget(GameObject* object);

	/// <summary>
	/// ���x�Z�b�g
	/// </summary>
	/// <param name="speed">���x</param>
	void SetSpeed(float speed) { this->speed = speed; }

	/// <summary>
	/// ���x�擾
	/// </summary>
	/// <returns>���x</returns>
	float Getspeed() { return speed; }

	/// <summary>
	/// �ڕW���W�ւ̕�������
	/// </summary>
	/// <returns>�ړ�����</returns>
	Vec3 DecideDir();

private:
	// �̃f�[�^
	Vec3 position{};
	float speed = 1.0f;
	Vec3 moveVec{};

	// �ڕW�f�[�^
	GameObject* object = nullptr;
	Vec3 targetPos{};

	// �����p�p�����[�^
	bool canMove = false;
	float accelSpeed = 0;
	const float moveTime  = 3.0f;	// �ړ�����
	const float accelTime = 1.0f;	// ��������
	const float decelTime = 0.5f;	// ��������
	const float stopTime  = 1.0f;	// ��~����

	Timer moveTimer;
	Timer easingTimer;
	int easingCnt = 0;
};