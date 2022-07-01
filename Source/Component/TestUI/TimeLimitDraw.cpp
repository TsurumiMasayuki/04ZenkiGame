#include "TimeLimitDraw.h"
#include "Component/TestUI/TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

void TimeLimitDraw::onStart()
{
	for (int i = 0; i < 10; i++)
	{
		objFirst[i]  = new GameObject(getUser().getGameMediator());
		objSecond[i] = new GameObject(getUser().getGameMediator());
		objFirst[i]->getTransform().setLocalPosition(Vec3{ -32, 330,10 });
        objFirst[i]->getTransform().setLocalScale(Vec3{ 64,64,1 });
        objSecond[i]->getTransform().setLocalPosition(Vec3{ 32,330,10 });
        objSecond[i]->getTransform().setLocalScale(Vec3{ 64,64,1 });


		numTexFirst[i] = objFirst[i]->addComponent<GUISpriteRenderer>();
		numTexSecond[i] = objSecond[i]->addComponent<GUISpriteRenderer>();
		numTexFirst[i]->setActive(false);
		numTexSecond[i]->setActive(false);
	}	

	GameObj = objFirst[0]->addComponent<TimeLimitUi>();

	numTexFirst[0]->setTextureByName("num0");
	numTexFirst[1]->setTextureByName("num1");
	numTexFirst[2]->setTextureByName("num2");
	numTexFirst[3]->setTextureByName("num3");
	numTexFirst[4]->setTextureByName("num4");
	numTexFirst[5]->setTextureByName("num5");
	numTexFirst[6]->setTextureByName("num6");
	numTexFirst[7]->setTextureByName("num7");
	numTexFirst[8]->setTextureByName("num8");
	numTexFirst[9]->setTextureByName("num9");

	numTexSecond[0]->setTextureByName("num0");
	numTexSecond[1]->setTextureByName("num1");
	numTexSecond[2]->setTextureByName("num2");
	numTexSecond[3]->setTextureByName("num3");
	numTexSecond[4]->setTextureByName("num4");
	numTexSecond[5]->setTextureByName("num5");
	numTexSecond[6]->setTextureByName("num6");
	numTexSecond[7]->setTextureByName("num7");
	numTexSecond[8]->setTextureByName("num8");
	numTexSecond[9]->setTextureByName("num9");
}

void TimeLimitDraw::onUpdate()
{
	if (!GameObj->isMin(TimeLimitUi::GetLimitFirst()))
	{
		numTexFirst[TimeLimitUi::GetLimitFirst()]->setActive(true);
			numTexSecond[TimeLimitUi::GetLimitSecond()]->setActive(true);
	}
	
	if (GameObj->isMin(TimeLimitUi::GetLimitSecond()))
	{
		for (int i = 0; i < 10; i++)
		{
			numTexSecond[i]->setActive(false);
		}

		TimeLimitUi::SetNum(TimeLimitUi::GetLimitSecond());
		TimeLimitUi::ReduceTime(TimeLimitUi::GetLimitFirst());
	}
}