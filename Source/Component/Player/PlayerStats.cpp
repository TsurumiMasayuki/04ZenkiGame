#include "PlayerStats.h"

PlayerStats::PlayerStats()
	: m_WalkTime(0.0f),
	m_DashTime(0.0f)
{
}

PlayerStats::PlayerStats(const nlohmann::json& json)
	: m_WalkTime((float)json["WalkTime"]),
	m_DashTime((float)json["DashTime"])
{
}
