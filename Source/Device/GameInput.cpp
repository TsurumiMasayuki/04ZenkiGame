#include "GameInput.h"
#include "Device/GameDevice.h"
#include "ControllerInput.h"

Vec3 GameInput::getPlayerMove()
{
	Vec3 result = Vec3::zero();

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		StickInput vec;
		if (!moveLock)
		{
			// 左スティックの傾き取得
			vec = ControllerInput::getInstance().getLStickInput();
		}
		else
		{
			// ロック状態なら移動量無し
			vec = { 0,0 };
		}

		result = Vec3(vec.x, 0, vec.y);
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		//入力に応じて移動方向をセット(マス目なので斜め移動はなし)
		//上
		if (input.isKey(DIK_UP))
			result += Vec3(0.0f, 0.0f, 1.0f);
		//下
		if (input.isKey(DIK_DOWN))
			result += Vec3(0.0f, 0.0f, -1.0f);
		//右
		if (input.isKey(DIK_RIGHT))
			result += Vec3(1.0f, 0.0f, 0.0f);
		//左
		if (input.isKey(DIK_LEFT))
			result += Vec3(-1.0f, 0.0f, 0.0f);
	}

	return result.normalized();
}

bool GameInput::getPlayerWalk()
{
	bool result;

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		StickInput vec;
		if (!moveLock)
		{
			// 左スティックの傾き取得
			return true;
		}
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		//入力に応じて移動方向をセット(マス目なので斜め移動はなし)
		//移動キーが入力されているか
		if (input.isKey(DIK_UP) ||
			input.isKey(DIK_DOWN) ||
			input.isKey(DIK_RIGHT) ||
			input.isKey(DIK_LEFT)
			)return true;
	}
}

bool GameInput::getPlayerDash()
{
	bool result;

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isTrigger(ControllerInput::PAD_TRIGGER::RIGHT);
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKey(DIK_SPACE);
	}

	return result;
}

bool GameInput::getPlayerDashStart()
{
	bool result;

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isTrigger(ControllerInput::PAD_TRIGGER::RIGHT);
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_SPACE);
	}

	return result;
}

bool GameInput::getPlayerDashEND()
{
	bool result;

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isTrigger(ControllerInput::PAD_TRIGGER::RIGHT);
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKeyUp(DIK_SPACE);
	}

	return result;
}

bool GameInput::getSliding()
{
	bool result;

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::X);
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_LCONTROL);
	}

	return result;
}

bool GameInput::getOption()
{
	bool result;

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START);
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_O);
	}

	return result;
}

bool GameInput::getOptionSelectUp()
{
	bool result{};

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{

	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_UP);
	}

	return result;
}

bool GameInput::getOptionSelectDown()
{
	bool result{};

	// コントローラー接続中
	if (ControllerInput::getInstance().isConnect())
	{
	
	}
	// キーボード
	else
	{
		//入力デバイスを取得
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_DOWN);
	}

	return result;
}
