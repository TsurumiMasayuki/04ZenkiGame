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
	/// <param name="scale">�{�� def : 0.1</param>
	/// <param name="stopTime">�K�p���� def : 0.5</param>
	void start(float scale = 0.1f, float stopTime = 0.5f);

	/// <summary>
	/// �X�V
	/// </summary>
	void update();

	/// <summary>
	/// ��~���Ă��邩
	/// </summary>
	/// <returns></returns>
	bool isStop() { return isStop; }

private:
	Timer stayTimer;
	
	float scale;
	float stopTime;

	bool isStop = false;
};