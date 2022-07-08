#include "TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
int  TimeLimitUi::firstNum = 0;
int  TimeLimitUi::secondNum = 3;
bool TimeLimitUi::isDead = false;

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