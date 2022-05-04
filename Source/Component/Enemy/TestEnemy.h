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

private:
	// �̃f�[�^
	Vec3 position{};
	float speed = 1.0f;
	Vec3 moveVec{};

	// �ڕW�f�[�^
	GameObject* object = nullptr;

	// �ڕW���W
	Vec3 targetPos{};

};