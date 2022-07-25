#include "PlayerParamManager.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

#include "Component/TestUI/TestUI.h"
#include "Option/Option.h"
#include "Component/Item/CollectItemUI.h"

#include "Component/Player/PlayerStats.h"
#include "Utility/JsonFileManager.h"
#include "Component/TestUI/TimeLimitDraw.h"
#include "Component/TestUI/LapTimeDraw.h"

void PlayerParamManager::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");

	//�I�v�V�����I�u�W�F�N�g����
	GameObject* optionObj = new GameObject(getUser().getGameMediator());
	m_Option = optionObj->addComponent<Option>();

	//�A�C�e���X�v���C�g
	GameObject* itemObj = new GameObject(getUser().getGameMediator());
	m_Item = itemObj->addComponent<CollectItemUI>();

	GameObject* timeLimitObj = new GameObject(getUser().getGameMediator());
	m_TimeLimit = timeLimitObj->addComponent<TimeLimitDraw>();

	GameObject* laptimeObj = new GameObject(getUser().getGameMediator());
	m_LapTime = laptimeObj->addComponent<LapTimeDraw>();
}

void PlayerParamManager::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	if (isHitEnemy)
	{
		if (m_RollingTime==0.0f)
		{
			m_RollingTime = 2.0f;
			isHitEnemy = false;
		}
		else
		{
			float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_AcceleratorSpeedUpTime;

			//����
			m_Acceleration += deltaTime * timeMultiplier;

			m_RollingTime -= deltaTime;
			m_RollingTime = std::fmaxf(0.0f, m_RollingTime);

		}

	}
	else
	{
		//�_�b�V���{�^����������Ă���Ȃ�
		if (GameInput::getInstance().getPlayerDash() && m_Fuel > 0.0f)
		{
			float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_DashSpeedUpTime;

			//����
			m_Acceleration += deltaTime * timeMultiplier;

			//�R������
			m_Fuel -= deltaTime;
			m_Fuel = std::fmaxf(0.0f, m_Fuel);
		}
		else if (!GameInput::getInstance().getPlayerDash())
		{
			//�R������
			m_Fuel += deltaTime;
			m_Fuel = std::fminf(5.0f, m_Fuel);
		}
	}
	if (GameInput::getInstance().getPlayerMove().z == 0.0f)
	{
		//�����x��0�ɂ���
		m_Acceleration = 0.0f;
	}
	else
	{
		float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_WalkSpeedUpTime;

		//����
		m_Acceleration += deltaTime * timeMultiplier;
	}

	//���b�N����Ă��Ȃ��Ȃ�ړ�������ݒ�
	if (!m_IsLock)
	{
		m_MoveDir = GameInput::getInstance().getPlayerMove();
		m_BaseMoveSpeed = m_Stats.m_WalkSpeed;
	}
}

bool PlayerParamManager::isFuelZero() const
{
	return m_Fuel <= 0.0f;
}

void PlayerParamManager::setAcceleration(float acceleration)
{
	m_Acceleration = acceleration;
}

float PlayerParamManager::getAcceleration() const
{
	return m_Acceleration;
}

void PlayerParamManager::onDamage()
{
	m_Acceleration = 0.0f;
}

void PlayerParamManager::lockPlayerMove(bool isLock)
{
	m_IsLock = isLock;
}

const Vec3& PlayerParamManager::getMoveDir() const
{
	return m_MoveDir;
}

void PlayerParamManager::setMoveDir(const Vec3& moveDir)
{
	m_MoveDir = moveDir;
}

float PlayerParamManager::getMoveSpeed() const
{
	return m_BaseMoveSpeed * (1.0f + m_Acceleration);
}

void PlayerParamManager::setMoveSpeed(float speed)
{
	m_BaseMoveSpeed = speed;
}
