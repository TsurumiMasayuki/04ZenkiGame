#include "PlayerParamManager.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

#include "Component/TestUI/TestUI.h"

void PlayerParamManager::onStart()
{
	//UI�I�u�W�F�N�g����
	GameObject* pTestUIObj = new GameObject(getUser().getGameMediator());
	//UI����
	m_pTestUI = pTestUIObj->addComponent<TestUI>();
}

void PlayerParamManager::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//�_�b�V���{�^����������Ă���Ȃ�
	if (GameInput::getInstance().getPlayerDash())
	{
		//����
		m_Acceleration += deltaTime * 0.25f;
		m_Acceleration = std::fminf(1.0f, m_Acceleration);

		//�R������
		m_Fuel -= deltaTime;
		m_Fuel = std::fmaxf(0.0f, m_Fuel);
	}
	else
	{
		//�R������
		m_Fuel += deltaTime;
		m_Fuel = std::fminf(5.0f, m_Fuel);
	}
	
	if (GameDevice::getInput().isKeyUp(DIK_SPACE))
	{
		//�����x��0�ɂ���
		m_Acceleration = 0.0f;
	}

	//UI�ɐݒ�
	m_pTestUI->SetParam(m_Health, m_Acceleration, m_Fuel);
}

bool PlayerParamManager::isFuelZero() const
{
	return m_Fuel <= 0.0f;
}

float PlayerParamManager::getAcceleration() const
{
	return m_Acceleration;
}
