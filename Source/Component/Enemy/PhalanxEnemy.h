#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Enemy/TestEnemy.h"

class PhalanxEnemy
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
	/// <param name="length">���� : 1</param>
	/// <param name="mainUnit">�{�̔ԍ� : 0</param>
	/// <param name="radius">�~�����a : 12.0f</param>
	/// <param name="speedX">Z�ړ����x : 1.0f</param>
	/// <param name="speedZ">��������</param>
	void init(Vec3 position, int length = 1, int mainUnit = 0, float radius = 12.0f, float speedZ = 1.0f);

	/// <summary>
	/// �U�ꕝ�ݒ�
	/// </summary>
	/// <param name="width">��</param>
	void setSwing(float width, float time = 1.0f) { swingWidth = width; turnaroundTime = time; }

	/// <summary>
	/// �ڕW�ݒ�
	/// </summary>
	/// <param name="targetobject">�ڕW�I�u�W�F�N�g</param>
	void setTarget(GameObject* targetobject) { target = targetobject; }
	
private:
	std::vector<GameObject*> vec_object;
	Vec3 cylinderCoord;

	int mainUnit = 0;	// �{�̔ԍ�

	float radius = 0;	// �~�����a

	float rotateSpeed = 0;
	float speedZ = 0;

	float swingWidth = 10.0f;	// �ӂ蕝
	float turnaroundTime = 1.0f;	// ��������
	float swingCnt = 0;

	GameObject* target = nullptr;	// �ڕW�I�u�W�F�N�g
};