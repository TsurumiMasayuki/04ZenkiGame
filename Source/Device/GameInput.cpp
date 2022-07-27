#include "GameInput.h"
#include "Device/GameDevice.h"
#include "ControllerInput.h"

Vec3 GameInput::getPlayerMove()
{
	Vec3 result = Vec3::zero();

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		StickInput vec;
		if (!moveLock)
		{
			// ���X�e�B�b�N�̌X���擾
			vec = ControllerInput::getInstance().getLStickInput();
		}
		else
		{
			// ���b�N��ԂȂ�ړ��ʖ���
			vec = { 0,0 };
		}

		result = Vec3(vec.x, 0, vec.y);
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		//���͂ɉ����Ĉړ��������Z�b�g(�}�X�ڂȂ̂Ŏ΂߈ړ��͂Ȃ�)
		//��
		if (input.isKey(DIK_UP))
			result += Vec3(0.0f, 0.0f, 1.0f);
		//��
		if (input.isKey(DIK_DOWN))
			result += Vec3(0.0f, 0.0f, -1.0f);
		//�E
		if (input.isKey(DIK_RIGHT))
			result += Vec3(1.0f, 0.0f, 0.0f);
		//��
		if (input.isKey(DIK_LEFT))
			result += Vec3(-1.0f, 0.0f, 0.0f);

		if (moveLock)
			result = Vec3::zero();
	}

	return result.normalized();
}

bool GameInput::getPlayerWalk()
{
	bool result;

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		StickInput vec;
		if (!moveLock)
		{
			// ���X�e�B�b�N�̌X���擾
			vec = ControllerInput::getInstance().getLStickInput();
			if (vec.x != 0 || vec.y != 0)
			{
				return true;
			}

		}
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		//���͂ɉ����Ĉړ��������Z�b�g(�}�X�ڂȂ̂Ŏ΂߈ړ��͂Ȃ�)
		//�ړ��L�[�����͂���Ă��邩
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

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isTrigger(ControllerInput::PAD_TRIGGER::RIGHT);
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKey(DIK_SPACE);
	}

	return result;
}

bool GameInput::getPlayerDashStart()
{
	bool result;

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isTrigger(ControllerInput::PAD_TRIGGER::RIGHT);
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_SPACE);
	}

	return result;
}

bool GameInput::getPlayerDashEND()
{
	bool result;

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isTrigger(ControllerInput::PAD_TRIGGER::RIGHT);
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKeyUp(DIK_SPACE);
	}

	return result;
}

bool GameInput::getSliding()
{
	bool result;

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::X);
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_LCONTROL);
	}

	return result;
}

bool GameInput::getOption()
{
	bool result;

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
		result = ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START);
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_O);
	}

	return result;
}

bool GameInput::getOptionSelectUp()
{
	bool result{};

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{

	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_UP);
	}

	return result;
}

bool GameInput::getOptionSelectDown()
{
	bool result{};

	// �R���g���[���[�ڑ���
	if (ControllerInput::getInstance().isConnect())
	{
	
	}
	// �L�[�{�[�h
	else
	{
		//���̓f�o�C�X���擾
		const auto& input = GameDevice::getInput();

		result = input.isKeyDown(DIK_DOWN);
	}

	return result;
}
