#include "LapTime.h"
int  LapTime::tenThousandPlace = 0;
int  LapTime::oneThousandPlace = 0;
int  LapTime::oneHundredPlace = 0;
int  LapTime::tenPlace = 0;
int  LapTime::onePlace = 0;
int  LapTime::tenThousandResult = 0;
int  LapTime::tenThousandResult1 = 0;
int  LapTime::tenThousandResult2 = 0;
int  LapTime::tenThousandResult3 = 0;
int  LapTime::oneThousandResult = 0;
int  LapTime::oneThousandResult1 = 0;
int  LapTime::oneThousandResult2 = 0;
int  LapTime::oneThousandResult3 = 0;
int  LapTime::oneHundredResult = 0;
int  LapTime::oneHundredResult1 = 0;
int  LapTime::oneHundredResult2 = 0;
int  LapTime::oneHundredResult3 = 0;
int  LapTime::tenResult = 0;
int  LapTime::tenResult1 = 0;
int  LapTime::tenResult2 = 0;
int  LapTime::tenResult3 = 0;
int  LapTime::oneResult = 0;
int  LapTime::oneResult1 = 0;
int  LapTime::oneResult2 = 0;
int  LapTime::oneResult3 = 0;
int LapTime::count = 0;

bool LapTime::isCount = false;

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
