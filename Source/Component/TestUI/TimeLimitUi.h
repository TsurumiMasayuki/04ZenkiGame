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

	static void Add(int& value,const int num)
	{
		value += num;
	}

	static void ResetTimer()
	{
		firstNum  = 9;
		secondNum = 9;
		thirdNum  = 9;
		forthNum  = 9;
	};

	static void set(float value);

	static int AddLimit(int value)
	{
		set(GetLimitFirst() + value);
		return GetLimitFirst();
	}

	static int& GetLimitFirst()
	{
		return firstNum;
	}

	static int& GetLimitSecond()
	{
		return secondNum;
	}

	static int& GetLimitThird()
	{
		return thirdNum;
	}

	static int& GetLimitforth()
	{
		return forthNum;
	}

	static void  SetNum(int& num)
	{
		num = 9;
	}

	static int& GetMax() { return maxValue; }

	static bool IsMax(int value){
		return (GetMax() <= value);
	}

	static bool isMin(int& value) { return value < 0; }

	static bool SetDead(bool dead) { return isDead = dead; }
	static bool& IsDead() { return isDead; }

	static bool SetStart(bool start) { return isStart = start; }
	static bool& IsStart() { return isStart; }
private:
	static int firstNum, secondNum, thirdNum,forthNum,maxValue,minValue;
	static bool isDead,isStart;
};