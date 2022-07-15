#pragma once
#include "Component/Base/AbstractComponent.h"
#include "PlayerStats.h"
#include "Component/TestUI/TestUI.h"
class TestUI;
class Option;
class CollectItemUI;
class TimeLimitDraw;

//プレイヤーのパラメータ管理
class PlayerParamManager
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	//燃料がゼロかどうか
	bool isFuelZero() const;

	//加速度を設定
	void setAcceleration(float acceleration);

	//加速度を取得
	float getAcceleration() const;

	void onDamage();

	//プレイヤーの移動をロックするかどうか
	void lockPlayerMove(bool isLock);

	//移動方向を取得
	const Vec3& getMoveDir() const;
	//移動方向を設定
	void setMoveDir(const Vec3& moveDir);

	void setHitEnemy() { isHitEnemy = true; }

	//移動速度を取得
	float getMoveSpeed() const;
	//移動速度を設定
	void setMoveSpeed(float speed);

private:
	Option* m_Option;
	CollectItemUI* m_Item;
	TimeLimitDraw* m_TimeLimit;
	TestUI* m_testUI;
	//体力
	float m_Health = 5.0f;
	//加速度を取得
	float m_Acceleration;
	//燃料
	float m_Fuel = 4.0f;

	float m_BaseMoveSpeed;
	Vec3 m_MoveDir;

	bool m_IsLock;
	PlayerStats m_Stats;

	bool isHitEnemy = false;
	float m_RollingTime = 2.0;
};