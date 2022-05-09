#pragma once
#include "Component/Base/AbstractComponent.h"

class TestUI;

//�v���C���[�̃p�����[�^�Ǘ�
class PlayerParamManager
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	//�R�����[�����ǂ���
	bool isFuelZero() const;

	//�����x���擾
	float getAcceleration() const;

private:
	TestUI* m_pTestUI;

	//�̗�
	float m_Health = 5.0f;
	//�����x���擾
	float m_Acceleration;
	//�R��
	float m_Fuel = 5.0f;
};