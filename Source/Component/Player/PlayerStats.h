#pragma once
#include "json.hpp"

struct PlayerStats
{
	PlayerStats();
	PlayerStats(const nlohmann::json& json);

	//1�}�X�ړ�����܂ł̎���
	float m_WalkTime;
	//�_�b�V������1�}�X�ړ�����܂ł̎���
	float m_DashTime;
};