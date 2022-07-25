#pragma once
#include "Utility/SingletonTemplate.h"
#include "Utility/Timer.h"

class HitStop
	: public SingletonTemplate<HitStop>
{
public:
	friend class SingletonTemplate<HitStop>;

	/// <summary>
	/// 始動
	/// </summary>
	/// <param name="scale">倍率 def : 0.1</param>
	/// <param name="stopTime">適用時間 def : 0.5</param>
	void start(float scale = 0.1f, float stopTime = 0.5f);

	/// <summary>
	/// 更新
	/// </summary>
	void update();

	/// <summary>
	/// 停止しているか
	/// </summary>
	/// <returns></returns>
	bool isStop() { return isStopFlag; }

private:
	Timer stayTimer;
	
	float scale;
	float stopTime;

	bool isStopFlag = false;
};