#include "TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
int  TimeLimitUi::firstNum = 9;
int  TimeLimitUi::secondNum = 9;
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