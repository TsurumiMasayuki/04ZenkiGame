#include "LapTime.h"
int  LapTime::tenThousandPlace = 0;
int  LapTime::oneThousandPlace = 0;
int  LapTime::oneHundredPlace = 0;
int  LapTime::tenPlace = 0;
int  LapTime::onePlace = 0;

void LapTime::onStart()
{

}

void LapTime::onUpdate()
{
	if (TimeLimitUi::IsStart())
	{
		AddTime(GetOnePlace());
		AddTime(GetOnePlace());
	}

	if (TimeLimitUi::IsDead())
	{
		ResetTimer();
	}

	if (GetOnePlace() > 9)
	{
		AddTime(GetTenPlace());
		onePlace = 0;
	}

	if (GetTenPlace() > 9)
	{
		AddTime(GetOneHundredPlace());
		tenPlace = 0;
	}

	if (GetOneHundredPlace() > 9)
	{
		AddTime(GetOneThousandPlace());
		oneHundredPlace = 0;
	}

	if (GetOneThousandPlace() > 9)
	{
		AddTime(GetTenThousandPlace());
		oneThousandPlace = 0;
	}
}
