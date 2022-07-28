#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"
#include "Component/TestUI/TimeLimitUi.h"
#include <vector>

class LapTime :
    public AbstractComponent
{
public:
	//AbstractComponent ÇâÓÇµÇƒåpè≥
	virtual void onStart() override;
	virtual void onUpdate() override;

	static void AddTime(int& num)
	{
		num += 1;
	}

	static int& GetTenThousandPlace()
	{
		return tenThousandPlace;
	}

	static int& GetOneThousandPlace()
	{
		return oneThousandPlace;
	}

	static int& GetOneHundredPlace()
	{
		return oneHundredPlace;
	}

	static int& GetTenPlace()
	{
		return tenPlace;
	}

	static int& GetOnePlace()
	{
		return onePlace;
	}

	static void ResetTimer()
	{
		tenThousandPlace = 0;
		oneThousandPlace = 0;
		oneHundredPlace  = 0;
		tenPlace = 0;
		onePlace = 0;
	};

	static void SetResult0()
	{
		tenThousandResult = GetTenThousandPlace();
		oneThousandResult = GetOneThousandPlace();
		oneHundredResult  = GetOneHundredPlace();
		tenResult = GetTenPlace();
		oneResult = GetOnePlace();
	}

	static void SetResult1()
	{
		tenThousandResult1 = GetTenThousandPlace();
		oneThousandResult1 = GetOneThousandPlace();
		oneHundredResult1 = GetOneHundredPlace();
		tenResult1 = GetTenPlace();
		oneResult1 = GetOnePlace();
	}

	static void SetResult2()
	{
		tenThousandResult2 = GetTenThousandPlace();
		oneThousandResult2 = GetOneThousandPlace();
		oneHundredResult2 = GetOneHundredPlace();
		tenResult2 = GetTenPlace();
		oneResult2 = GetOnePlace();
	}

	static void SetResult3()
	{
		tenThousandResult3 = GetTenThousandPlace();
		oneThousandResult3 = GetOneThousandPlace();
		oneHundredResult3 = GetOneHundredPlace();
		tenResult3 = GetTenPlace();
		oneResult3 = GetOnePlace();
	}

	static int& GetResultTenThousand()
	{
		return tenThousandResult;
	}
	static int& GetResultOneThousand()
	{
		return oneThousandResult;
	}
	static int& GetResultOneHundred()
	{
		return oneHundredResult;
	}
	static int& GetResultTen()
	{
		return tenResult;
	}
	static int& GetResultOne()
	{
		return oneResult;
	}

	static int& GetResultTenThousand1()
	{
		return tenThousandResult1;
	}
	static int& GetResultOneThousand1()
	{
		return oneThousandResult1;
	}
	static int& GetResultOneHundred1()
	{
		return oneHundredResult1;
	}
	static int& GetResultTen1()
	{
		return tenResult1;
	}
	static int& GetResultOne1()
	{
		return oneResult1;
	}

	static int& GetResultTenThousand20()
	{
		return tenThousandResult2;
	}
	static int& GetResultOneThousand20()
	{
		return oneThousandResult2;
	}
	static int& GetResultOneHundred20()
	{
		return oneHundredResult2;
	}
	static int& GetResultTen20()
	{
		return tenResult2;
	}
	static int& GetResultOne20()
	{
		return oneResult2;
	}

	static int& GetResultTenThousand3()
	{
		return tenThousandResult3;
	}
	static int& GetResultOneThousand3()
	{
		return oneThousandResult3;
	}
	static int& GetResultOneHundred3()
	{
		return oneHundredResult3;
	}
	static int& GetResultTen3()
	{
		return tenResult3;
	}
	static int& GetResultOne3()
	{
		return oneResult3;
	}

	static bool SetCount(bool dead) { return isCount = dead; }
	static bool& GetCount() { return isCount; }

	static void AddCo()
	{
		count += 1;
	}

	static int& GetCo(){
		return count;
	}
private:
	static int tenThousandPlace,oneThousandPlace,oneHundredPlace,tenPlace,onePlace;
	static int tenThousandResult, oneThousandResult, oneHundredResult, tenResult, oneResult;
	static int tenThousandResult1, oneThousandResult1, oneHundredResult1, tenResult1, oneResult1;
	static int tenThousandResult2, oneThousandResult2, oneHundredResult2, tenResult2, oneResult2;
	static int tenThousandResult3, oneThousandResult3, oneHundredResult3, tenResult3, oneResult3;
	static int count;
	static bool isCount;
};

