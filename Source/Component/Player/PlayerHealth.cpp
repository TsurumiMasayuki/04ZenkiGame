#include "PlayerHealth.h"

void PlayerHealth::onStart()
{
	//�v���C���[��HP��100�ɂ���
	m_PlayerHP = 100;
}

void PlayerHealth::onUpdate()
{
	//���t���[��10�񕜂�����
	m_PlayerHP += 10;
}