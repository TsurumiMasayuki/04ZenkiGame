#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"

class PressEnemy
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
	/// 目標オブジェクトセット
	/// </summary>
	/// <param name="object">目標</param>
	void setTarget(GameObject* object) { targetObj = object; }

	/// <summary>
	/// 押しつぶす
	/// </summary>
	void press();

private:
	Vec3 position{};
	Vec3 velocity{};
	float radius = 0;

	GameObject* targetObj = nullptr;

	bool isPress = false;
};