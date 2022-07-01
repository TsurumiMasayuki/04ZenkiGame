#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class JumpingEnemy
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
	/// <param name="speedZ"></param>
	/// <param name="speedY"></param>
	/// <param name="radius"></param>
	void init(Vec3 position, float speedZ, float speedY, float radius = 11.0f);

	/// <summary>
	/// �ڕW�ݒ�
	/// </summary>
	/// <param name="target">�ڕW�I�u�W�F�N�g</param>
	void setTarget(GameObject* target) { targetObject = target; }

	/// <summary>
	/// �W�����v�̃p�����[�^�[�ݒ�
	/// </summary>
	/// <param name="hight">����</param>
	/// <param name="interval">�ҋ@����</param>
	void setJumpParameter(float hight = 1.0f, float interval = 1.0f);

private:
	GameObject* targetObject = nullptr;

	// �I�u�W�F�N�g���
	Vec3 position{};
	Vec3 velocity{};
	Vec3 cylinderCoord{};

	// �X�e�[�W���
	float radius = 0.0f;
	Vec3 centerPoint = Vec3(0, 0, 0);

	// �W�����v�̃p�����[�^�[
	float hight = 1.0f;
	float interval = 1.0f;

	Timer intervalTimer;

	float cycleCnt = 0;
};