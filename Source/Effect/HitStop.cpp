#include "HitStop.h"
#include "Device/GameDevice.h"

void HitStop::start(float scale, float stopTime)
{
	// タイムスケールをセット
	GameDevice::getGameTime().m_TimeScale = scale;

	// デルタタイムからの束縛解除
	stayTimer.setUseUnscaledTime(true);

	// タイマーセット
	stayTimer.setMaxTime(stopTime);
	// タイマー開始
	stayTimer.reset();

	isStop = true;
}

void HitStop::update()
{
	if (isStop)
	{
		// 一定時間で元に戻す
		if (stayTimer.isTime())
		{
			// タイムスケールをセット
			GameDevice::getGameTime().m_TimeScale = 1.0f;

			isStop = false;
		}

		// タイマー更新
		stayTimer.update();
	}
}
