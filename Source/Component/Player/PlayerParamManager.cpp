#include "PlayerParamManager.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

#include "Component/TestUI/TestUI.h"
#include "Option/Option.h"
#include "Component/Item/CollectItemUI.h"

#include "Component/Player/PlayerStats.h"
#include "Utility/JsonFileManager.h"
#include "Component/TestUI/TimeLimitDraw.h"

void PlayerParamManager::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");

	//UIオブジェクト生成
	GameObject* pTestUIObj = new GameObject(getUser().getGameMediator());
	//UI生成
	m_pTestUI = pTestUIObj->addComponent<TestUI>();

	//オプションオブジェクト生成
	GameObject* optionObj = new GameObject(getUser().getGameMediator());
	m_Option = optionObj->addComponent<Option>();

	//アイテムスプライト
	GameObject* itemObj = new GameObject(getUser().getGameMediator());
	m_Item = itemObj->addComponent<CollectItemUI>();

	GameObject* timeLimitObj = new GameObject(getUser().getGameMediator());
	m_TimeLimit = timeLimitObj->addComponent<TimeLimitDraw>();
}

void PlayerParamManager::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//ダッシュボタンが押されているなら
	if (GameInput::getInstance().getPlayerDash() && m_Fuel > 0.0f)
	{
		float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_DashSpeedUpTime;

		//加速
		m_Acceleration += deltaTime * timeMultiplier;

		//燃料減少
		m_Fuel -= deltaTime;
		m_Fuel = std::fmaxf(0.0f, m_Fuel);
	}
	else if (!GameInput::getInstance().getPlayerDash())
	{
		//燃料増加
		m_Fuel += deltaTime;
		m_Fuel = std::fminf(5.0f, m_Fuel);
	}

	if (GameInput::getInstance().getPlayerMove().z == 0.0f)
	{
		//加速度を0にする
		m_Acceleration = 0.0f;
	}
	else
	{
		float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_WalkSpeedUpTime;

		//加速
		m_Acceleration += deltaTime * 0.1f;
	}

	//UIに設定
	m_pTestUI->SetParam(m_Health, m_Acceleration, m_Fuel);

	m_Acceleration = std::fminf(1.0f, m_Acceleration);

	//ロックされていないなら移動方向を設定
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
