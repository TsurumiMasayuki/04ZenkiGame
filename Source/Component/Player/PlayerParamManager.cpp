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

	//オプションオブジェクト生成
	GameObject* optionObj = new GameObject(getUser().getGameMediator());
	m_Option = optionObj->addComponent<Option>();

	//アイテムスプライト
	GameObject* itemObj = new GameObject(getUser().getGameMediator());
	m_Item = itemObj->addComponent<CollectItemUI>();

	GameObject* timeLimitObj = new GameObject(getUser().getGameMediator());
	m_TimeLimit = timeLimitObj->addComponent<TimeLimitDraw>();

	GameObject* testUIObj = new GameObject(getUser().getGameMediator());
	m_testUI = testUIObj->addComponent<TestUI>();
}


void PlayerParamManager::onUpdate()
{
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	m_KnockBack -= m_KnockBack.normalized() * 3.0f * GameDevice::getGameTime().getDeltaTime();

	//通常時
	if (GameInput::getInstance().getPlayerMove().z == 0.0f)
	{
		//加速度を0にする
		m_Acceleration = 0.0f;
	}
	else
	{
		float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_WalkSpeedUpTime;

		//加速
		if (m_Acceleration < JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_WalkSpeed)
			m_Acceleration += deltaTime * timeMultiplier;
	}

	//敵撃破関連
	if (isHitEnemy)
	{
		if (m_RollingTime==0.0f)
		{
			m_RollingTime = 2.0f;
			attackStock--;
			isHitEnemy = false;
		}
		else
		{
			float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_AcceleratorSpeedUpTime;

			//加速
			if(m_Acceleration< JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_AcceleratorSpeed)
				m_Acceleration += deltaTime * timeMultiplier;

			m_RollingTime -= deltaTime;
			m_RollingTime = std::fmaxf(0.0f, m_RollingTime);

		}

	}
	//ローリング時
	if (GameInput::getInstance().getPlayerDash())
	{
		float timeMultiplier = 1.0f / JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_DashSpeedUpTime;

		//加速
		if (m_Acceleration < JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_DashSpeed)
			m_Acceleration += deltaTime * timeMultiplier;

	}


	//ロックされていないなら移動方向を設定
	if (!m_IsLock)
	{
		m_MoveDir = GameInput::getInstance().getPlayerMove();
		m_BaseMoveSpeed = m_Stats.m_WalkSpeed;
	}
	//UIクラスへ加速度を渡す
	m_testUI->SetAcceleration(m_Acceleration);
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

void PlayerParamManager::addKnockBack(const Vec3& knockback)
{
	m_KnockBack += knockback;
}

const Vec3& PlayerParamManager::getKnockBack()
{
	return m_KnockBack;
}

float PlayerParamManager::getMoveSpeed() const
{
	return m_BaseMoveSpeed * (1.0f + m_Acceleration);
}

void PlayerParamManager::setMoveSpeed(float speed)
{
	m_BaseMoveSpeed = speed;
}

void PlayerParamManager::attackStockAddition()
{
	if(attackStock<4)attackStock++;
}
