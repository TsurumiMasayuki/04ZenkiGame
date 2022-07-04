#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"
#include <vector>

class TimeLimitUi :
    public AbstractComponent
{
public:
	//AbstractComponent ÇâÓÇµÇƒåpè≥
	virtual void onStart() override;
	virtual void onUpdate() override;

	static void ReduceTime(int& value)
	{
		value -= 1;
	}

	static void AddTime(int& value)
	{
		value += 1;
	}

	static int& GetLimitFirst()
	{
		return firstNum;
	}

	static int& GetLimitSecond()
	{
		return secondNum;
	}

	static void  SetNum(int& num)
	{
		num = 9;
	}

	static bool isMin(int& value) { return value < 0; }
private:
	Timer limitTimer;
	static int firstNum, secondNum;
};