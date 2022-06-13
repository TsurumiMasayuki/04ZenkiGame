#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class JumpingEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent を介して継承されました
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="position">初期座標</param>
	/// <param name="speedZ"></param>
	/// <param name="speedY"></param>
	/// <param name="radius"></param>
	void init(Vec3 position, float speedZ, float speedY, float radius = 11.0f);

	/// <summary>
	/// 目標設定
	/// </summary>
	/// <param name="target">目標オブジェクト</param>
	void setTarget(GameObject* target) { targetObject = target; }

	/// <summary>
	/// ジャンプのパラメーター設定
	/// </summary>
	/// <param name="hight">高さ</param>
	/// <param name="interval">待機時間</param>
	void setJumpParameter(float hight = 1.0f, float interval = 1.0f);

private:
	GameObject* targetObject = nullptr;

	// オブジェクト情報
	Vec3 position{};
	Vec3 velocity{};
	Vec3 cylinderCoord{};

	// ステージ情報
	float radius = 0.0f;
	Vec3 centerPoint = Vec3(0, 0, 0);

	// ジャンプのパラメーター
	float hight = 1.0f;
	float interval = 1.0f;

	Timer intervalTimer;

	float cycleCnt = 0;
};