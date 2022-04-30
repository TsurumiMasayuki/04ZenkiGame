#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"

class TestEnemy
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

private:
	// 個体データ
	Vec3 position{};
	float speed = 1.0f;
	Vec3 moveVec{};

	// 目標データ
	GameObject* object = nullptr;

	// 目標座標
	Vec3 targetPos{};

};