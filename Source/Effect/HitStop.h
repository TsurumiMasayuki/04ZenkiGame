#pragma once
#include "Utility/SingletonTemplate.h"
#include "Utility/Timer.h"

class HitStop
	: public SingletonTemplate<HitStop>
{
public:
	friend class SingletonTemplate<HitStop>;

	/// <summary>
	/// �n��
	/// </summary>
	void Start(float scale = 0.1f, float stopTime = 1.0f);

	/// <summary>
	/// �X�V
	/// </summary>
	void update();

private:
	Timer stayTimer;
	
	float scale;
	float stopTime;
};