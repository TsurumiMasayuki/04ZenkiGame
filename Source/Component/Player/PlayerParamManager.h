#pragma once
#include "Component/Base/AbstractComponent.h"

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

	//�����x���擾
	float getAcceleration() const;

	void onDamage();

private:
	TestUI* m_pTestUI;
	Option* m_Option;
	CollectItemUI* m_Item;
	TimeLimitDraw* m_TimeLimit;

	//�̗�
	float m_Health = 5.0f;
	//�����x���擾
	float m_Acceleration;
	//�R��
	float m_Fuel = 5.0f;
};