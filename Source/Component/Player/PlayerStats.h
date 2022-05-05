#pragma once
#include "json.hpp"

struct PlayerStats
{
	PlayerStats();
	PlayerStats(const nlohmann::json& json);

	//1マス移動するまでの時間
	float m_WalkTime;
	//ダッシュ中に1マス移動するまでの時間
	float m_DashTime;
	//炎が残る時間
	float m_FlameRemainTime;
};