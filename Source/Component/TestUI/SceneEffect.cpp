#include "SceneEffect.h"

void SceneEffect::onStart()
{

}

void SceneEffect::onUpdate()
{
    if (callNum == 0)
	{
	//シーン開始処理
	  drawPos = drawObject->getTransform().getLocalPosition();
	   if (drawStartFlg)
	   {
		 drawSprite->setActive(true);

		 if (FirstDraw())
		 {
			if (SecondDraw())
			{
				if (ThirdDraw())
				{
					FourthDraw();
				}
			}
		 }
	   }
	}
	else if (callNum == 1)
	{
		//シーン終了処理
		erasePos = eraseObject->getTransform().getLocalPosition();
		if (startFlg)
		{
			eraseSprite->setActive(true);
			for (int i = 0; i < 4; i++)
			{
				maskSprite[i]->setActive(true);
			}
			if (FirstErase())
			{
				if (SecondErase())
				{
					if (ThirdErase())
					{
						FourthErase();
					}
				}
			}
		}
	}
   
}

void SceneEffect::Initialize(short callNum)
{
	this->callNum = callNum;
	if (callNum == 0)
	{
		//シーン開始共通初期化
		drawObject = new GameObject(getUser().getGameMediator());
		drawSprite = drawObject->addComponent<GUISpriteRenderer>();
		drawSprite->setActive(false);
		for (int i = 0; i < 4; i++)
		{
			drawMaskObj[i] = new GameObject(getUser().getGameMediator());
			drawTotalVelocity[i] = 2560;
		}
		for (int i = 0; i < 4; i++)
		{
			drawMaskSprite[i] = drawMaskObj[i]->addComponent<GUISpriteRenderer>();
		}
		drawSprite->setTextureByName("erase");
		for (int i = 0; i < 4; i++)
		{
			drawMaskSprite[i]->setTextureByName("mask");
		}
		//シーン開始個別初期化
		drawObject->getTransform().setLocalPosition(Vec3{ 640,270,1 });
		drawObject->getTransform().setLocalScale(Vec3{ 240,180,1 });
		drawSprite->setActive(false);
		drawMaskObj[0]->getTransform().setLocalPosition(Vec3{ -640,270,1 });
		drawMaskStartPos[0] = drawMaskObj[0]->getTransform().getLocalPosition();
		drawMaskObj[0]->getTransform().setLocalScale(Vec3{ 2560,180,1 });
		drawMaskObj[1]->getTransform().setLocalPosition(Vec3{ -640,90,1 });
		drawMaskStartPos[1] = drawMaskObj[0]->getTransform().getLocalPosition();
		drawMaskObj[1]->getTransform().setLocalScale(Vec3{ 2560,180,1 });
		drawMaskObj[2]->getTransform().setLocalPosition(Vec3{ -640,-90,1 });
		drawMaskStartPos[2] = drawMaskObj[0]->getTransform().getLocalPosition();
		drawMaskObj[2]->getTransform().setLocalScale(Vec3{ 2560,180,1 });
		drawMaskObj[3]->getTransform().setLocalPosition(Vec3{ -640,-270,1 });
		drawMaskStartPos[3] = drawMaskObj[0]->getTransform().getLocalPosition();
		drawMaskObj[3]->getTransform().setLocalScale(Vec3{ 2560,180,1 });
	}
	else if (callNum == 1)
	{
		//シーン終了共通初期化
		eraseObject = new GameObject(getUser().getGameMediator());
		for (int i = 0; i < 4; i++)
		{
			maskObject[i] = new GameObject(getUser().getGameMediator());
			totalVelocity[i] = 0;
		}
		eraseSprite = eraseObject->addComponent<GUISpriteRenderer>();
		eraseSprite->setActive(false);
		for (int i = 0; i < 4; i++)
		{
			maskSprite[i] = maskObject[i]->addComponent<GUISpriteRenderer>();
			maskSprite[i]->setActive(false);
		}
		eraseSprite->setTextureByName("erase");
		for (int i = 0; i < 4; i++)
		{
			maskSprite[i]->setTextureByName("mask");
		}
		//シーン終了個別初期化
		eraseObject->getTransform().setLocalPosition(Vec3{ -640,270,1 });
		eraseObject->getTransform().setLocalScale(Vec3{ 240,180,1 });
		eraseSprite->setActive(false);
		maskObject[0]->getTransform().setLocalPosition(Vec3{ -640,270,1 });
		maskStartPos[0] = maskObject[0]->getTransform().getLocalPosition();
		maskObject[0]->getTransform().setLocalScale(Vec3{ 0,180,1 });
		maskObject[1]->getTransform().setLocalPosition(Vec3{ -640,90,1 });
		maskStartPos[1] = maskObject[1]->getTransform().getLocalPosition();
		maskObject[1]->getTransform().setLocalScale(Vec3{ 0,180,1 });
		maskObject[2]->getTransform().setLocalPosition(Vec3{ -640,-90,1 });
		maskStartPos[2] = maskObject[2]->getTransform().getLocalPosition();
		maskObject[2]->getTransform().setLocalScale(Vec3{ 0,180,1 });
		maskObject[3]->getTransform().setLocalPosition(Vec3{ -640,-270,1 });
		maskStartPos[3] = maskObject[3]->getTransform().getLocalPosition();
		maskObject[3]->getTransform().setLocalScale(Vec3{ 0,180,1 });

	}
}

void SceneEffect::StartEffect()
{
	if (callNum == 0)
	{
		drawStartFlg = true;
	}
	else if (callNum == 1)
	{
		startFlg = true;
	}
}

bool SceneEffect::IsEnd()
{
	if (callNum == 0)
	{
		return endDrawFlg;
	}
	else if (callNum == 1)
	{
		return endEraseFlg;
	}
}

bool SceneEffect::FirstErase()
{
	if (firstEndFlg)
	{
		return true;
	}
	if (!firstRePosFlg)
	{
		firstRePosFlg = true;
		eraseObject->getTransform().setLocalPosition(Vec3{ -520,270,1 });
		erasePos = eraseObject->getTransform().getLocalPosition();
	}
	totalVelocity[0] += VELOCITY;
	eraseObject->getTransform().setLocalPosition(Vec3{ erasePos.x + VELOCITY,erasePos.y,erasePos.z });
	maskObject[0]->getTransform().setLocalScale(Vec3{ totalVelocity[0]*2,180,1 });
	if (erasePos.x > 1280)
	{
		firstEndFlg = true;
		return true;
	}

	return false;
}

bool SceneEffect::SecondErase()
{
	
	if (secondEndFlg)
	{
		return true;
	}
	if (!secondRePosFlg)
	{
		secondRePosFlg = true;
		eraseObject->getTransform().setLocalPosition(Vec3{ -520,90,1 });
		erasePos = eraseObject->getTransform().getLocalPosition();
	}
	totalVelocity[1] += VELOCITY;
	eraseObject->getTransform().setLocalPosition(Vec3{ erasePos.x + VELOCITY,erasePos.y,erasePos.z });
	maskObject[1]->getTransform().setLocalScale(Vec3{ totalVelocity[1]*2,180,1 });
	if (erasePos.x > 1280)
	{
		secondEndFlg = true;
		return true;
	}

	return false;
}

bool SceneEffect::ThirdErase()
{

	if (thirdEndFlg)
	{
		return true;
	}
	if (!thirdRePosFlg)
	{
		thirdRePosFlg = true;
		eraseObject->getTransform().setLocalPosition(Vec3{ -520,-90,1 });
		erasePos = eraseObject->getTransform().getLocalPosition();
	}
	totalVelocity[2] += VELOCITY;
	eraseObject->getTransform().setLocalPosition(Vec3{ erasePos.x + VELOCITY,erasePos.y,erasePos.z });
	maskObject[2]->getTransform().setLocalScale(Vec3{ totalVelocity[2]*2,180,1 });
	if (erasePos.x > 1280)
	{
		thirdEndFlg = true;
		return true;
	}

	return false;
}

bool SceneEffect::FourthErase()
{
	if (fourthEndFlg)
	{
		return true;
	}
	if (!fourthRePosFlg)
	{
		fourthRePosFlg = true;
		eraseObject->getTransform().setLocalPosition(Vec3{ -520,-270,1 });
		erasePos = eraseObject->getTransform().getLocalPosition();
	}
	totalVelocity[3] += VELOCITY;
	eraseObject->getTransform().setLocalPosition(Vec3{ erasePos.x + VELOCITY,erasePos.y,erasePos.z });
	maskObject[3]->getTransform().setLocalScale(Vec3{ totalVelocity[3] * 2,180,1 });
	if (erasePos.x > 1280)
	{
		fourthEndFlg = true;
		endEraseFlg = true;
		return true;
	}

	return false;
}

bool SceneEffect::FirstDraw()
{
	if (drawFirstEndFlg)
	{
		return true;
	}
	if (!drawFirstRePosFlg)
	{
		drawFirstRePosFlg = true;
		drawObject->getTransform().setLocalPosition(Vec3{ 520,270,1 });
		drawPos = drawObject->getTransform().getLocalPosition();
	}
	drawTotalVelocity[0] -= VELOCITY*2;
	drawObject->getTransform().setLocalPosition(Vec3{ drawPos.x - VELOCITY,drawPos.y,drawPos.z });
	drawMaskObj[0]->getTransform().setLocalScale(Vec3{ drawTotalVelocity[0] ,180,1 });
	if (drawPos.x < -750)
	{
		drawMaskObj[0]->getTransform().setLocalScale(Vec3{ 0 ,180,1 });
		drawFirstEndFlg = true;
		return true;
	}

	return false;
}

bool SceneEffect::SecondDraw()
{

	if (drawSecondEndFlg)
	{
		return true;
	}
	if (!drawSecondRePosFlg)
	{
		drawSecondRePosFlg = true;
		drawObject->getTransform().setLocalPosition(Vec3{ 520,90,1 });
		drawPos = drawObject->getTransform().getLocalPosition();
	}
	drawTotalVelocity[1] -= VELOCITY*2;
	drawObject->getTransform().setLocalPosition(Vec3{ drawPos.x - VELOCITY,drawPos.y,drawPos.z });
	drawMaskObj[1]->getTransform().setLocalScale(Vec3{ drawTotalVelocity[1],180,1 });
	if (drawPos.x < -750)
	{
		drawMaskObj[1]->getTransform().setLocalScale(Vec3{ 0 ,180,1 });
		drawSecondEndFlg = true;
		return true;
	}

	return false;
}

bool SceneEffect::ThirdDraw()
{

	if (drawThirdEndFlg)
	{
		return true;
	}
	if (!drawThirdRePosFlg)
	{
		drawThirdRePosFlg = true;
		drawObject->getTransform().setLocalPosition(Vec3{ 520,-90,1 });
		drawPos = drawObject->getTransform().getLocalPosition();
	}
	drawTotalVelocity[2] -= VELOCITY*2;
	drawObject->getTransform().setLocalPosition(Vec3{ drawPos.x - VELOCITY,drawPos.y,drawPos.z });
	drawMaskObj[2]->getTransform().setLocalScale(Vec3{ drawTotalVelocity[2],180,1 });
	if (drawPos.x < -750)
	{
		drawMaskObj[2]->getTransform().setLocalScale(Vec3{ 0 ,180,1 });
		drawThirdEndFlg = true;
		return true;
	}

	return false;
}
bool SceneEffect::FourthDraw()
{
	if (drawFourthEndFlg)
	{
		return true;
	}
	if (!drawFourthRePosFlg)
	{
		drawFourthRePosFlg = true;
		drawObject->getTransform().setLocalPosition(Vec3{ 520,-270,1 });
		drawPos = drawObject->getTransform().getLocalPosition();
	}
	drawTotalVelocity[3] -= VELOCITY*2;
	drawObject->getTransform().setLocalPosition(Vec3{ drawPos.x - VELOCITY,drawPos.y,drawPos.z });
	drawMaskObj[3]->getTransform().setLocalScale(Vec3{ drawTotalVelocity[3],180,1 });
	if (drawPos.x < -750)
	{
		drawMaskObj[3]->getTransform().setLocalScale(Vec3{ 0 ,180,1 });
		drawFourthEndFlg = true;
		endDrawFlg = true;
		return true;
	}

	return false;
}

