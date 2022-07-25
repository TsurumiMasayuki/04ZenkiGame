#include "LapTimeDraw.h"
#include "Component/TestUI/TimeLimitUi.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"

void LapTimeDraw::onStart()
{
	pointObject = new GameObject(getUser().getGameMediator());
	pointObject->getTransform().setLocalPosition(Vec3{ (float)-448,318,10 });
	pointObject->getTransform().setLocalScale(Vec3{ 16,16,1 });
	pointSprite = pointObject->addComponent<GUISpriteRenderer>();
	pointSprite->setTextureByName("point");

	colonObject = new GameObject(getUser().getGameMediator());
	colonObject->getTransform().setLocalPosition(Vec3{ (float)-552,330,10 });
	colonObject->getTransform().setLocalScale(Vec3{ 16,48,1 });
	colonSprite = colonObject->addComponent<GUISpriteRenderer>();
	colonSprite->setTextureByName("colon");

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			lapTimeObject[i][j] = new GameObject(getUser().getGameMediator());
			lapTimeObject[i][j]->getTransform().setLocalPosition(Vec3{ (float)-530 + (32 * i),330,10 });
			lapTimeObject[i][j]->getTransform().setLocalScale(Vec3{32,32,1});

			lapTimeSprite[i][j] = lapTimeObject[i][j]->addComponent<GUISpriteRenderer>();
			lapTimeSprite[i][j]->setActive(false);
		}
	}

	timeObject  = new GameObject(getUser().getGameMediator());
	timeObject->getTransform().setLocalPosition(Vec3{ (float)-600,330,10 });
	timeObject->getTransform().setLocalScale(Vec3{ 64,32,1 });
	timeSprite = timeObject->addComponent<GUISpriteRenderer>();
	timeSprite->setTextureByName("time");

	SetSprite(&lapTimeSprite[0]);
	GameObj = lapTimeObject[0][0]->addComponent<LapTime>();
}

void LapTimeDraw::onUpdate()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bool firstNum  = LapTime::GetTenThousandPlace() == j;
			bool secondNum = LapTime::GetOneThousandPlace() == j;
			bool thirdNum = LapTime::GetOneHundredPlace() == j;
			bool forthNum = LapTime::GetTenPlace() == j;
			bool fifthNum = LapTime::GetOnePlace() == j;

			lapTimeSprite[0][j]->setActive(firstNum);
			lapTimeSprite[1][j]->setActive(secondNum);
			lapTimeSprite[2][j]->setActive(thirdNum);
			lapTimeSprite[3][j]->setActive(forthNum);
			lapTimeSprite[4][j]->setActive(fifthNum);
		}
	}
}

void LapTimeDraw::SetSprite(GUISpriteRenderer* sprite[5][10])
{
	for (int i = 0; i < 5; i++)
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