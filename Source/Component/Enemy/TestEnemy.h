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

	void init(float angle, float speed = 1.0f, float radius = 11.0f, Vec3 centerPoint = Vec3(0, 0, 0));

	void setCenter(Vec3 centerPoint) { this->centerPoint = centerPoint; }

	void setRadius(float radius) { this->rasius = radius; }

	/// <summary>
	/// 移動方向指定
	/// </summary>
	/// <param name="angle">角度(°)</param>
	void setVecAngle(float angle) { this->angle = angle; }

	/// <summary>
	/// 移動方向取得
	/// </summary>
	/// <returns>角度(°)</returns>
	float getVecAngle() { return angle; }

	/// <summary>
	/// 速度セット
	/// </summary>
	/// <param name="speed">速度</param>
	void setSpeed(float speed) { this->speed = speed; }

	/// <summary>
	/// 速度取得
	/// </summary>
	/// <returns>速度</returns>
	float getspeed() { return speed; }

private:
	// 個体データ
	float angle = 0;
	Vec3 position{};
	float speed = 1.0f;
	Vec3 moveVec{};

	// ステージ情報
	float rasius = 0;
	Vec3 centerPoint = Vec3(0, 0, 0);
};
