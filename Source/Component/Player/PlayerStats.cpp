#include "PlayerStats.h"

PlayerStats::PlayerStats()
	: m_WalkSpeedUpTime(0.0f),
	m_DashSpeedUpTime(0.0f),
	m_FlameRemainTime(0.0f)
{
}

PlayerStats::PlayerStats(const nlohmann::json& json)
	: m_FlameRemainTime((float)json["FlameRemainTime"]),
	m_WalkSpeed((float)json["WalkSpeed"]),
	m_DashSpeed((float)json["DashSpeed"]),
	m_WalkSpeedUpTime((float)json["WalkSpeedUpTime"]),
	m_DashSpeedUpTime((float)json["DashSpeedUpTime"])
{
}
