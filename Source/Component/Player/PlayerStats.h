#pragma once
#include "json.hpp"

struct PlayerStats
{
	PlayerStats();
	PlayerStats(const nlohmann::json& json);

	//炎が残る時間
	float m_FlameRemainTime;

	//移動速度(自由移動)
	float m_WalkSpeed;
	//ダッシュ速度
	float m_DashSpeed;
	//加速時速度
	float m_AcceleratorSpeed;

	//移動の加速時間
	float m_WalkSpeedUpTime;
	//ダッシュの加速時間
	float m_DashSpeedUpTime;
	//加速状態の加速時間
	float m_AcceleratorSpeedUpTime;
};