#pragma once
#include "Component/Base/AbstractComponent.h"
#include "PlayerStats.h"

class TestUI;
class Option;
class CollectItemUI;
class TimeLimitDraw;

//�v���C���[�̃p�����[�^�Ǘ�
class PlayerParamManager
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	//�R�����[�����ǂ���
	bool isFuelZero() const;

	//�����x��ݒ�
	void setAcceleration(float acceleration);

	//�����x���擾
	float getAcceleration() const;

	void onDamage();

	//�v���C���[�̈ړ������b�N���邩�ǂ���
	void lockPlayerMove(bool isLock);

	//�ړ��������擾
	const Vec3& getMoveDir() const;
	//�ړ�������ݒ�
	void setMoveDir(const Vec3& moveDir);

	void setHitEnemy() { isHitEnemy = true; }

	//�ړ����x���擾
	float getMoveSpeed() const;
	//�ړ����x��ݒ�
	void setMoveSpeed(float speed);

private:
	Option* m_Option;
	CollectItemUI* m_Item;
	TimeLimitDraw* m_TimeLimit;

	//�̗�
	float m_Health = 5.0f;
	//�����x���擾
	float m_Acceleration;
	//�R��
	float m_Fuel = 4.0f;

	float m_BaseMoveSpeed;
	Vec3 m_MoveDir;

	bool m_IsLock;
	PlayerStats m_Stats;

	bool isHitEnemy = false;
	float m_RollingTime = 2.0;
};