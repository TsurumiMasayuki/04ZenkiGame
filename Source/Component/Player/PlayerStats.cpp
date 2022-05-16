#include "PlayerStats.h"

PlayerStats::PlayerStats()
	: m_WalkTime(0.0f),
	m_DashTime(0.0f),
	m_FlameRemainTime(0.0f)
{
}

PlayerStats::PlayerStats(const nlohmann::json& json)
	: m_WalkTime((float)json["WalkTime"]),
	m_DashTime((float)json["DashTime"]),
	m_FlameRemainTime((float)json["FlameRemainTime"]),
	m_WalkSpeed(2.0f),
	m_DashSpeed(2.0f)
{
}
