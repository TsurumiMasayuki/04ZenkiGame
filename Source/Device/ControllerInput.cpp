#include "ControllerInput.h"
#include "Math/MathUtility.h"

constexpr SHORT JOYSTICK_CENTER = 32767;

void ControllerInput::update()
{
	//前フレームの状態をコピー
	m_PrePadInfo = m_CurPadInfo;

	//コントローラーの接続状態をオフにする
	m_IsPadConnected = false;

	//接続されているコントローラーを探す
	for (int i = 0; i < 4; i++)
	{
		//問題なく接続されているコントローラーが見つかったら終了
		if (XInputGetState(i, &m_CurPadInfo) == JOYERR_NOERROR)
		{
			//接続されているのでオンにする
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
	//左入力されていたら
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		axis.x = -1;
		axis.y = 0;
	}

	//右入力されていたら
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		axis.x = 1;
		axis.y = 0;
	}

	//上入力されていたら
	if (m_CurPadInfo.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		axis.x = 0;
		axis.y = 1;
	}

	//上入力されていたら
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

	//-1 ~ 1の間に変換
	if (x != 0)
		axis.x = MathUtility::clamp(x / (float)JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1の間に変換(Yの場合は符号を逆にする)
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

	//-1 ~ 1の間に変換
	if (x != 0)
		axis.x = MathUtility::clamp(x / JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1の間に変換(Yの場合は符号を逆にする)
	if (y != 0)
		axis.y = MathUtility::clamp(y / JOYSTICK_CENTER, -1.0f, 1.0f);

	return axis;
}

bool ControllerInput::isPadButton(PAD_BUTTON button) const
{
	return m_IsPadConnected &&
		//ボタンが押されているか
		(m_CurPadInfo.Gamepad.wButtons & (DWORD)button) &&
		//ボタンが押されているか
		(m_PrePadInfo.Gamepad.wButtons & (DWORD)button);
}

bool ControllerInput::isPadButtonUp(PAD_BUTTON button) const
{
	return m_IsPadConnected &&
		//ボタンが押されていないか
		!(m_CurPadInfo.Gamepad.wButtons & (DWORD)button) &&
		//ボタンが押されているか
		(m_PrePadInfo.Gamepad.wButtons & (DWORD)button);
}

bool ControllerInput::isPadButtonDown(PAD_BUTTON button) const
{
	return m_IsPadConnected &&
		//ボタンが押されているか
		(m_CurPadInfo.Gamepad.wButtons & (DWORD)button) &&
		//ボタンが押されていないか
		!(m_PrePadInfo.Gamepad.wButtons & (DWORD)button);
}

bool ControllerInput::isTrigger(PAD_TRIGGER trigger) const
{
	//右と左でトリガー切り替え
	BYTE curTrigger = trigger == PAD_TRIGGER::LEFT ? m_CurPadInfo.Gamepad.bLeftTrigger : m_CurPadInfo.Gamepad.bRightTrigger;

	//右と左でトリガー切り替え
	BYTE preTrigger = trigger == PAD_TRIGGER::LEFT ? m_PrePadInfo.Gamepad.bLeftTrigger : m_PrePadInfo.Gamepad.bRightTrigger;

	return m_IsPadConnected &&
		//ボタンが押されているか
		(curTrigger > 0) &&
		//ボタンが押されているか
		(preTrigger > 0);
}

bool ControllerInput::isTriggerUp(PAD_TRIGGER trigger) const
{
	//右と左でトリガー切り替え
	BYTE curTrigger = trigger == PAD_TRIGGER::LEFT ? m_CurPadInfo.Gamepad.bLeftTrigger : m_CurPadInfo.Gamepad.bRightTrigger;

	//右と左でトリガー切り替え
	BYTE preTrigger = trigger == PAD_TRIGGER::LEFT ? m_PrePadInfo.Gamepad.bLeftTrigger : m_PrePadInfo.Gamepad.bRightTrigger;

	return m_IsPadConnected &&
		//ボタンが押されていないか
		!(curTrigger > 0) &&
		//ボタンが押されているか
		(preTrigger > 0);
}

bool ControllerInput::isTriggerDown(PAD_TRIGGER trigger) const
{
	//右と左でトリガー切り替え
	BYTE curTrigger = trigger == PAD_TRIGGER::LEFT ? m_CurPadInfo.Gamepad.bLeftTrigger : m_CurPadInfo.Gamepad.bRightTrigger;

	//右と左でトリガー切り替え
	BYTE preTrigger = trigger == PAD_TRIGGER::LEFT ? m_PrePadInfo.Gamepad.bLeftTrigger : m_PrePadInfo.Gamepad.bRightTrigger;

	return m_IsPadConnected &&
		//ボタンが押されているか
		(curTrigger > 0) &&
		//ボタンが押されていないか
		!(preTrigger > 0);
}