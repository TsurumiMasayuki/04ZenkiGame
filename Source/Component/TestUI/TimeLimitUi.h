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

	static void ResetNum(int& numFirst, int& numSecond)
	{
		numFirst = 9;
		numSecond = 9;
	}

	static bool isMin(int& value) { return value < 0; }

	static bool SetDead(bool dead) { return isDead = dead; }

	static bool& IsDead() { return isDead; }

private:
	Timer limitTimer;
	static int firstNum, secondNum;
	static bool isDead;
};