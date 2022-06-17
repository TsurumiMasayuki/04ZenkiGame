#include "PlayerParamManager.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

#include "Component/TestUI/TestUI.h"
#include "Option/Option.h"
#include "Component/Item/CollectItem.h"

void PlayerParamManager::onStart()
{
	//UIオブジェクト生成
	GameObject* pTestUIObj = new GameObject(getUser().getGameMediator());
	//UI生成
	m_pTestUI = pTestUIObj->addComponent<TestUI>();

	//オプションオブジェクト生成
	GameObject* optionObj = new GameObject(getUser().getGameMediator());
	m_Option = optionObj->addComponent<Option>();

	//アイテムスプライト
	GameObject* itemObj = new GameObject(getUser().getGameMediator());
	m_Item = itemObj->addComponent<CollectItem>();
}

void PlayerParamManager::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//ダッシュボタンが押されているなら
	if (GameInput::getInstance().getPlayerDash() && m_Fuel > 0.0f)
	{
		//加速
		m_Acceleration += deltaTime * 0.1f;
		m_Acceleration = std::fminf(1.0f, m_Acceleration);

		//燃料減少
		m_Fuel -= deltaTime;
		m_Fuel = std::fmaxf(0.0f, m_Fuel);
	}
	else
	{
		//燃料増加
		m_Fuel += deltaTime;
		m_Fuel = std::fminf(5.0f, m_Fuel);
	}
	
	if (!GameInput::getInstance().getPlayerDash())
	{
		//加速度を0にする
		m_Acceleration = 0.0f;
	}

	//UIに設定
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
