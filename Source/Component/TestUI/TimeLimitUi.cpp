#include "TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
int  TimeLimitUi::firstNum = 6;
int  TimeLimitUi::secondNum = 0;

void TimeLimitUi::onStart()
{
	limitTimer.setMaxTime(1.0f);
}

void TimeLimitUi::onUpdate()
{
	limitTimer.update();

	if (limitTimer.getCurrentTime() >= 1.0f)
	{
		limitTimer.reset();
		ReduceTime(GetLimitSecond());
	}
}