#pragma once
#include "json.hpp"

struct PlayerStats
{
	PlayerStats();
	PlayerStats(const nlohmann::json& json);

	//�����c�鎞��
	float m_FlameRemainTime;

	//�ړ����x(���R�ړ�)
	float m_WalkSpeed;
	//�_�b�V�����x
	float m_DashSpeed;
	//���������x
	float m_AcceleratorSpeed;

	//�ړ��̉�������
	float m_WalkSpeedUpTime;
	//�_�b�V���̉�������
	float m_DashSpeedUpTime;
	//������Ԃ̉�������
	float m_AcceleratorSpeedUpTime;
};