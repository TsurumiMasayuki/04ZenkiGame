#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class Zigzagenemy
	: AbstractComponent
{
public:
	// AbstractComponent を介して継承されました
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="speedY">横移動力</param>
	/// <param name="speedZ">奥移動力</param>
	/// <param name="radius">円筒半径</param>
	void init(Vec3 position, float speedY, float speedZ, float radius = 11.0f);

	/// <summary>
	/// 折り返し
	/// </summary>
	void wrap();

private:
	Vec3 position{};
	Vec3 velocity{};
	float radius = 0;

	int dir = false;

	Timer wrapTimer;
};