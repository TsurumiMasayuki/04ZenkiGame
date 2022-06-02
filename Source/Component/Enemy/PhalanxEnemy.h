#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Enemy/TestEnemy.h"

class PhalanxEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void onStart() override;
	virtual void onUpdate() override;
	
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	/// <param name="position">‰ŠúÀ•W</param>
	/// <param name="length">’·‚³ : 1</param>
	/// <param name="mainUnit">–{‘Ì”Ô† : 0</param>
	/// <param name="radius">‰~“›”¼Œa : 11.0f</param>
	/// <param name="speedX">ZˆÚ“®‘¬“x : 1.0f</param>
	/// <param name="speedZ">”½•œŠÔ</param>
	void init(Vec3 position, int length = 1, int mainUnit = 0, float radius = 11.0f, float speedZ = 1.0f);

	/// <summary>
	/// U‚ê•İ’è
	/// </summary>
	/// <param name="width">•</param>
	void setSwing(float width, float time = 1.0f) { swingWidth = width; turnaroundTime = time; }
	
private:
	std::vector<GameObject*> vec_object;
	Vec3 cylinderCoord;

	int mainUnit = 0;	// –{‘Ì”Ô†

	float radius = 0;	// ‰~“›”¼Œa

	float rotateSpeed = 0;
	float speedZ = 0;

	float swingWidth = 10.0f;	// ‚Ó‚è•
	float turnaroundTime = 1.0f;	// ‰•œŠÔ
	float swingCnt = 0;
};