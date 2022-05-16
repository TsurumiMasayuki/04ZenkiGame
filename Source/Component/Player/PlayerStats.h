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
	//�����c�鎞��
	float m_FlameRemainTime;

	//�ړ����x(���R�ړ�)
	float m_WalkSpeed;
	//�_�b�V�����x
	float m_DashSpeed;
};