#include "TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
#include <algorithm>

int  TimeLimitUi::firstNum  = 9;
int  TimeLimitUi::secondNum = 9;
int  TimeLimitUi::thirdNum  = 9;
int  TimeLimitUi::forthNum  = 9;

int  TimeLimitUi::maxValue  = 9;
int  TimeLimitUi::minValue  = 0;

bool TimeLimitUi::isDead = false;
bool TimeLimitUi::isStart = false;

void TimeLimitUi::onStart()
{

}

void TimeLimitUi::onUpdate()
{
	//“ü—Í‚ðŽæ“¾
	auto& gameInput = GameInput::getInstance();

	if (gameInput.getPlayerWalk())
	{
		SetStart(true);
	}

	if (IsStart())
	{
		ReduceTime(GetLimitforth());
		ReduceTime(GetLimitforth());
	}

	if (GetLimitforth() < 0)
	{
		ReduceTime(GetLimitThird());
		forthNum = 9;
	}

	if (GetLimitThird() < 0)
	{
		ReduceTime(GetLimitSecond());
		thirdNum = 9;
	}

	if (GetLimitSecond() < 0)
	{
		ReduceTime(GetLimitFirst());
		secondNum = 9;
	}
}

void TimeLimitUi::set(float value)
{
	value = min(value, maxValue);
	value = max(value, minValue);
	firstNum = value;
}
