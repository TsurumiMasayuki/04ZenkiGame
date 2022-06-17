#include "PlayerParamManager.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

#include "Component/TestUI/TestUI.h"
#include "Option/Option.h"
#include "Component/Item/CollectItem.h"

#include "Component/Player/PlayerStats.h"
#include "Utility/JsonFileManager.h"

void PlayerParamManager::onStart()
{
	//UI�I�u�W�F�N�g����
	GameObject* pTestUIObj = new GameObject(getUser().getGameMediator());
	//UI����
	m_pTestUI = pTestUIObj->addComponent<TestUI>();

	//�I�v�V�����I�u�W�F�N�g����
	GameObject* optionObj = new GameObject(getUser().getGameMediator());
	m_Option = optionObj->addComponent<Option>();

	//�A�C�e���X�v���C�g
	GameObject* itemObj = new GameObject(getUser().getGameMediator());
	m_Item = itemObj->addComponent<CollectItem>();
}

void PlayerParamManager::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

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

	if (GameInput::getInstance().getPlayerMove().z == 0.0f)
	{
		//�����x��0�ɂ���
		m_Acceleration = 0.0f;
	}
	else
	{
		float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_WalkSpeedUpTime;

		//����
		m_Acceleration += deltaTime * 0.1f;
	}

	//UI�ɐݒ�
	m_pTestUI->SetParam(m_Health, m_Acceleration, m_Fuel);

	m_Acceleration = std::fminf(1.0f, m_Acceleration);
}

bool PlayerParamManager::isFuelZero() const
{
	return m_Fuel <= 0.0f;
}

float PlayerParamManager::getAcceleration() const
{
	return m_Acceleration;
}
