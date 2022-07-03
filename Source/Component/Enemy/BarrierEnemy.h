#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class BarrierEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent を介して継承されました
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">初期座標</param>
	/// <param name="speedZ">奥移動量</param>
	/// <param name="speedY">横移動量</param>
	/// <param name="radius">円筒半径</param>
	void init(Vec3 position, float speedZ, float speedY, float radius = 11.0f);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="object"></param>
	void setTarget(GameObject* object) { targetObj = object; }

private:
	Vec3 position{};
	Vec3 velocity{};
	float radius = 0;

	GameObject* targetObj;

	Vec3 rotation{};
	float ratateSpeed = 0.0f;

};