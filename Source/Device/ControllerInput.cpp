#include "ControllerInput.h"
#include "Math/MathUtility.h"

constexpr SHORT JOYSTICK_CENTER = 32767;

void ControllerInput::update()
{
	//�O�t���[���̏�Ԃ��R�s�[
	m_PrePadInfo = m_CurPadInfo;

	//�R���g���[���[�̐ڑ���Ԃ��I�t�ɂ���
	m_IsPadConnected = false;

	//�ڑ�����Ă���R���g���[���[��T��
	for (int i = 0; i < 4; i++)
	{
		//���Ȃ��ڑ�����Ă���R���g���[���[������������I��
		if (XInputGetState(i, &m_CurPadInfo) == JOYERR_NOERROR)
		{
			//�ڑ�����Ă���̂ŃI���ɂ���
			m_IsPadConnected = true;
			break;
		}
	}
}

DPadInput ControllerInput::getDPadInput() const
{
	if (!m_IsPadConnected)
		return { 0, 0 };

	DPadInput axis = { 0, 0 };
	//�����͂���Ă�����
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		axis.x = -1;
		axis.y = 0;
	}

	//�E���͂���Ă�����
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		axis.x = 1;
		axis.y = 0;
	}

	//����͂���Ă�����
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		axis.x = 0;
		axis.y = 1;
	}

	//����͂���Ă�����
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		axis.x = 0;
		axis.y = -1;
	}

	return axis;
}

StickInput ControllerInput::getLStickInput() const
{
	if (!m_IsPadConnected)
		return { 0.0f, 0.0f };

	StickInput axis(0, 0);
	float x = m_CurPadInfo.Gamepad.sThumbLX;
	float y = m_CurPadInfo.Gamepad.sThumbLY;

	//-1 ~ 1�̊Ԃɕϊ�
	if (x != 0)
		axis.x = MathUtility::clamp(x / (float)JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1�̊Ԃɕϊ�(Y�̏ꍇ�͕������t�ɂ���)
	if (y != 0)
		axis.y = MathUtility::clamp(y / (float)JOYSTICK_CENTER, -1.0f, 1.0f);

	return axis;
}

StickInput ControllerInput::getRStickInput() const
{
	if (!m_IsPadConnected)
		return { 0.0f, 0.0f };

	StickInput axis(0, 0);
	float x = m_CurPadInfo.Gamepad.sThumbRX;
	float y = m_CurPadInfo.Gamepad.sThumbRY;

	//-1 ~ 1�̊Ԃɕϊ�
	if (x != 0)
		axis.x = MathUtility::clamp(x / JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1�̊Ԃɕϊ�(Y�̏ꍇ�͕������t�ɂ���)
	if (y != 0)
		axis.y = MathUtility::clamp(y / JOYSTICK_CENTER, -1.0f, 1.0f);

	return axis;
}

bool ControllerInput::isPadButton(PAD_BUTTON button) const
{
	return m_IsPadConnected &&
		//�{�^����������Ă��邩
		(m_CurPadInfo.Gamepad.wButtons & (DWORD)button) &&
		//�{�^����������Ă��邩
		(m_PrePadInfo.Gamepad.wButtons & (DWORD)button);
}

bool ControllerInput::isPadButtonUp(PAD_BUTTON button) const
{
	return m_IsPadConnected &&
		//�{�^����������Ă��Ȃ���
		!(m_CurPadInfo.Gamepad.wButtons & (DWORD)button) &&
		//�{�^����������Ă��邩
		(m_PrePadInfo.Gamepad.wButtons & (DWORD)button);
}

bool ControllerInput::isPadButtonDown(PAD_BUTTON button) const
{
	return m_IsPadConnected &&
		//�{�^����������Ă��邩
		(m_CurPadInfo.Gamepad.wButtons & (DWORD)button) &&
		//�{�^����������Ă��Ȃ���
		!(m_PrePadInfo.Gamepad.wButtons & (DWORD)button);
}

bool ControllerInput::isTrigger(PAD_TRIGGER trigger) const
{
	//�E�ƍ��Ńg���K�[�؂�ւ�
	BYTE curTrigger = trigger == PAD_TRIGGER::LEFT ? m_CurPadInfo.Gamepad.bLeftTrigger : m_CurPadInfo.Gamepad.bRightTrigger;

	//�E�ƍ��Ńg���K�[�؂�ւ�
	BYTE preTrigger = trigger == PAD_TRIGGER::LEFT ? m_PrePadInfo.Gamepad.bLeftTrigger : m_PrePadInfo.Gamepad.bRightTrigger;

	return m_IsPadConnected &&
		//�{�^����������Ă��邩
		(curTrigger > 0) &&
		//�{�^����������Ă��邩
		(preTrigger > 0);
}

bool ControllerInput::isTriggerUp(PAD_TRIGGER trigger) const
{
	//�E�ƍ��Ńg���K�[�؂�ւ�
	BYTE curTrigger = trigger == PAD_TRIGGER::LEFT ? m_CurPadInfo.Gamepad.bLeftTrigger : m_CurPadInfo.Gamepad.bRightTrigger;

	//�E�ƍ��Ńg���K�[�؂�ւ�
	BYTE preTrigger = trigger == PAD_TRIGGER::LEFT ? m_PrePadInfo.Gamepad.bLeftTrigger : m_PrePadInfo.Gamepad.bRightTrigger;

	return m_IsPadConnected &&
		//�{�^����������Ă��Ȃ���
		!(curTrigger > 0) &&
		//�{�^����������Ă��邩
		(preTrigger > 0);
}

bool ControllerInput::isTriggerDown(PAD_TRIGGER trigger) const
{
	//�E�ƍ��Ńg���K�[�؂�ւ�
	BYTE curTrigger = trigger == PAD_TRIGGER::LEFT ? m_CurPadInfo.Gamepad.bLeftTrigger : m_CurPadInfo.Gamepad.bRightTrigger;

	//�E�ƍ��Ńg���K�[�؂�ւ�
	BYTE preTrigger = trigger == PAD_TRIGGER::LEFT ? m_PrePadInfo.Gamepad.bLeftTrigger : m_PrePadInfo.Gamepad.bRightTrigger;

	return m_IsPadConnected &&
		//�{�^����������Ă��邩
		(curTrigger > 0) &&
		//�{�^����������Ă��Ȃ���
		!(preTrigger > 0);
}