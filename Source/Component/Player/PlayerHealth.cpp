#include "PlayerHealth.h"

void PlayerHealth::onStart()
{
	//プレイヤーのHPを100にする
	m_PlayerHP = 100;
}

void PlayerHealth::onUpdate()
{
	//毎フレーム10回復させる
	m_PlayerHP += 10;
}