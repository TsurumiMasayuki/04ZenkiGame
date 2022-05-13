#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "Utility/SingletonTemplate.h"

struct StickInput
{
	float x;
	float y;
};

struct DPadInput
{
	int x;
	int y;
};

class ControllerInput
	: public SingletonTemplate<ControllerInput>
{
public:
	//�R���g���[���[�̃{�^���w��pEnum
	enum class PAD_BUTTON
	{
		X = 0x4000,		//X�{�^��
		Y = 0x8000,		//Y�{�^��
		A = 0x1000,		//A�{�^��
		B = 0x2000,		//B�{�^��
		LB = 0x0100,	//L�{�^��
		RB = 0x0200,	//R�{�^��
		START = 0x0010,	//Start�{�^��
		BACK = 0x0020	//Back�{�^��
	};

	enum class PAD_TRIGGER
	{
		LEFT,
		RIGHT
	};

	friend class SingletonTemplate<ControllerInput>;

	void update();

	// �R���g���[���[���ڑ�����Ă��邩�̎擾
	bool isConnect() const { return m_IsPadConnected; }

	//�R���g���[���[�̃{�^��������������Ă��邩����
	bool isPadButton(PAD_BUTTON button) const;
	//�R���g���[���[�̃{�^���������ꂽ�u�Ԃ�����
	bool isPadButtonUp(PAD_BUTTON button) const;
	//�R���g���[���[�̃{�^���������ꂽ�u�Ԃ�����
	bool isPadButtonDown(PAD_BUTTON button) const;

	//���X�e�B�b�N�̓��͂��擾
	StickInput getLStickInput() const;
	//�E�X�e�B�b�N�̓��͂��擾
	StickInput getRStickInput() const;

	//�\���{�^���̓��͂��擾
	DPadInput getDPadInput() const;

	//�R���g���[���[�̃{�^��������������Ă��邩����
	bool isTrigger(PAD_TRIGGER trigger) const;
	//�R���g���[���[�̃{�^���������ꂽ�u�Ԃ�����
	bool isTriggerUp(PAD_TRIGGER trigger) const;
	//�R���g���[���[�̃{�^���������ꂽ�u�Ԃ�����
	bool isTriggerDown(PAD_TRIGGER trigger) const;

protected:
	//�R���X�g���N�^���B��
	ControllerInput() {};
	//�f�X�g���N�^���B��
	virtual ~ControllerInput() {};

private:
	//�R���g���[���[���ڑ�����Ă��邩
	bool m_IsPadConnected;

	//���݂̃t���[���̃R���g���[���[���
	XINPUT_STATE m_CurPadInfo;
	//��O�̃t���[���̃R���g���[���[���
	XINPUT_STATE m_PrePadInfo;
};