#include "TimeLimitDraw.h"
#include "Component/TestUI/TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

void TimeLimitDraw::onStart()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			timeLimitObject[i][j] = new GameObject(getUser().getGameMediator());
			timeLimitObject[i][j]->getTransform().setLocalPosition(Vec3{ (float)-530 + (64 * i),266,10 });
			timeLimitObject[i][j]->getTransform().setLocalScale(Vec3{ 64,64,1 });
		
			timeLimitSprite[i][j] = timeLimitObject[i][j]->addComponent<GUISpriteRenderer>();
			timeLimitSprite[i][j]->setActive(false);
		}
	}

	SetSprite(&timeLimitSprite[0]);
	GameObj = timeLimitObject[0][0]->addComponent<TimeLimitUi>();
}

void TimeLimitDraw::onUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bool firstNum  = TimeLimitUi::GetLimitFirst()  == j;
			bool secondNum = TimeLimitUi::GetLimitSecond() == j;

			timeLimitSprite[0][j]->setActive(firstNum);
			timeLimitSprite[1][j]->setActive(secondNum);
		}
	}

	if (GameObj->isMin(TimeLimitUi::GetLimitFirst()))
	{
		GameObj->SetDead(true);
		GameObj->ResetTimer();
		GameObj->SetStart(false);
	}
	
	if (GameObj->isMin(TimeLimitUi::GetLimitSecond()))
	{
		TimeLimitUi::SetNum(TimeLimitUi::GetLimitSecond());
		TimeLimitUi::ReduceTime(TimeLimitUi::GetLimitFirst());
	}
}

void TimeLimitDraw::SetSprite(GUISpriteRenderer* sprite[3][10])
{
	for (int i = 0; i < 4; i++)
	{
		sprite[i][0]->setTextureByName("num0");
		sprite[i][1]->setTextureByName("num1");
		sprite[i][2]->setTextureByName("num2");
		sprite[i][3]->setTextureByName("num3");
		sprite[i][4]->setTextureByName("num4");
		sprite[i][5]->setTextureByName("num5");
		sprite[i][6]->setTextureByName("num6");
		sprite[i][7]->setTextureByName("num7");
		sprite[i][8]->setTextureByName("num8");
		sprite[i][9]->setTextureByName("num9");
	}
}
