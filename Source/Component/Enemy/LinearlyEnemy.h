#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class LinearlyEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent を介して継承
	virtual void onStart() override;
	virtual void onUpdate() override;

public:
	/// <summary>
	/// 目標オブジェクトセット
	/// </summary>
	/// <param name="object">目標オブジェクト</param>
	void SetTarget(GameObject* object);

	/// <summary>
	/// 速度セット
	/// </summary>
	/// <param name="speed">速度</param>
	void SetSpeed(float speed) { this->speed = speed; }

	/// <summary>
	/// 速度取得
	/// </summary>
	/// <returns>速度</returns>
	float Getspeed() { return speed; }

	/// <summary>
	/// 目標座標への方向決定
	/// </summary>
	/// <returns>移動方向</returns>
	Vec3 DecideDir();

private:
	// 個体データ
	Vec3 position{};
	float speed = 1.0f;
	Vec3 moveVec{};

	// 目標データ
	GameObject* object = nullptr;
	Vec3 targetPos{};

	// 加速用パラメータ
	bool canMove = false;
	float accelSpeed = 0;
	const float moveTime  = 3.0f;	// 移動時間
	const float accelTime = 1.0f;	// 加速時間
	const float decelTime = 0.5f;	// 減速時間
	const float stopTime  = 1.0f;	// 停止時間

	Timer moveTimer;
	Timer easingTimer;
	int easingCnt = 0;
};