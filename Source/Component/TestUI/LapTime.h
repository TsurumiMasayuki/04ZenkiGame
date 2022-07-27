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

private:
	static int tenThousandPlace,oneThousandPlace,oneHundredPlace,tenPlace,onePlace;
	static bool isDead;
};

