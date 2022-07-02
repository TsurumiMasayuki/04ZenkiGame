#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Enemy/TestEnemy.h"

class PhalanxEnemy
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
	/// <param name="length">長さ : 1</param>
	/// <param name="mainUnit">本体番号 : 0</param>
	/// <param name="radius">円筒半径 : 11.0f</param>
	/// <param name="speedX">Z移動速度 : 1.0f</param>
	/// <param name="speedZ">反復時間</param>
	void init(Vec3 position, int length = 1, int mainUnit = 0, float radius = 11.0f, float speedZ = 1.0f);

	/// <summary>
	/// 振れ幅設定
	/// </summary>
	/// <param name="width">幅</param>
	void setSwing(float width, float time = 1.0f) { swingWidth = width; turnaroundTime = time; }

	/// <summary>
	/// 目標設定
	/// </summary>
	/// <param name="targetobject">目標オブジェクト</param>
	void setTarget(GameObject* targetobject) { target = targetobject; }
	
private:
	std::vector<GameObject*> vec_object;
	Vec3 cylinderCoord;

	int mainUnit = 0;	// 本体番号

	float radius = 0;	// 円筒半径

	float rotateSpeed = 0;
	float speedZ = 0;

	float swingWidth = 10.0f;	// ふり幅
	float turnaroundTime = 1.0f;	// 往復時間
	float swingCnt = 0;

	GameObject* target = nullptr;	// 目標オブジェクト
};