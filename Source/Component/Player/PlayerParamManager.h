#pragma once
#include "Component/Base/AbstractComponent.h"

class TestUI;
class Option;

//プレイヤーのパラメータ管理
class PlayerParamManager
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	//燃料がゼロかどうか
	bool isFuelZero() const;

	//加速度を取得
	float getAcceleration() const;

private:
	TestUI* m_pTestUI;
	Option* m_Option;

	//体力
	float m_Health = 5.0f;
	//加速度を取得
	float m_Acceleration;
	//燃料
	float m_Fuel = 5.0f;
};