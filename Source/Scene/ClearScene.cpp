#include "ClearScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/D2DTextRenderer.h"
#include "Device/GameDevice.h"
#include "Device/ControllerInput.h"
#include "Component/TestUI/LapTime.h"

std::string ClearScene::nextScene()
{
	return "Title";
}

bool ClearScene::isEnd()
{
	return m_pSceneEndEffect->IsEnd();
}

void ClearScene::start()
{
	//背景スプライト
	ClearObject = new GameObject(this);
	ClearObject->getTransform().setLocalPosition(Vec3{ 0,0,1 });
	ClearObject->getTransform().setLocalScale(Vec3{ 680,720,1 });

	ClearSprite = ClearObject->addComponent<SpriteRenderer>();
	ClearSprite->setTextureByName("backGround");

	//クリアスプライト
	resultContents.resultClear = new GameObject(this);
	resultContents.resultClearSprite = resultContents.resultClear->addComponent<GUISpriteRenderer>();
	resultContents.resultClearSprite->setTextureByName("ui_clear");
	resultContents.resultClearSprite->getTransform().setLocalPosition(Vec3{ 0,200,1.5f });
	resultContents.resultClearSprite->getTransform().setLocalScale(Vec3{ 300,150,1 });

	//総合スプライト
	resultContents.resultComprehensive = new GameObject(this);
	resultContents.resultComprehensiveSprite = resultContents.resultComprehensive->addComponent<GUISpriteRenderer>();
	resultContents.resultComprehensiveSprite->setTextureByName("ui_sougou");
	resultContents.resultComprehensiveSprite->getTransform().setLocalPosition(Vec3{ -200,-150,1.5f });
	resultContents.resultComprehensiveSprite->getTransform().setLocalScale(Vec3{ 300,100,1.0 });

	//チェックポイントスプライト
	for (int i = 0; i < 2; i++)
    {
	    resultContents.resultCheckPoint[i] = new GameObject(this);
		resultContents.resultCheckPointSprite[i] = resultContents.resultCheckPoint[i]->addComponent<GUISpriteRenderer>();
		resultContents.resultCheckPointSprite[i]->getTransform().setLocalPosition(Vec3{ -200,50 - ((float)i * 100),1.5f });
		resultContents.resultCheckPointSprite[i]->getTransform().setLocalScale(Vec3{ 300,100,1 });
	}
	resultContents.resultCheckPointSprite[0]->setTextureByName("ui_check1");
	resultContents.resultCheckPointSprite[1]->setTextureByName("ui_check2");

	//チェックポイント数値
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)                
			{
				resultContents.lapTimeObject[i][j][k] = new GameObject(this);
				resultContents.lapTimeSprite[i][j][k] = resultContents.lapTimeObject[i][j][k]->addComponent<GUISpriteRenderer>();
				resultContents.lapTimeSprite[i][j][k]->setActive(true);
				resultContents.lapTimeSprite[i][j][k]->getTransform().setLocalPosition(Vec3{ (float)50 + (64 * j) ,(float)50 - (100 * i),1.5f});
				resultContents.lapTimeSprite[i][j][k]->getTransform().setLocalScale(Vec3{ 64,64,1.0f });
			}
		}
	}

	SetSprite(&resultContents.lapTimeSprite[0]);

	//棒線スプライト
	for (int i = 0; i < 3; i++)
    {
    	resultContents.resultBar[i] = new GameObject(this);
		resultContents.resultBarSprite[i] = resultContents.resultBar[i]->addComponent<GUISpriteRenderer>();
		resultContents.resultBarSprite[i]->setTextureByName("ui_line");
		resultContents.resultBarSprite[i]->getTransform().setLocalScale(Vec3{ 332,100,1 });
		resultContents.resultBarSprite[i]->getTransform().setLocalPosition(Vec3{ 184,0 - ((float)i * 100),1.5f });
    }

	//リザルト画面
	resultBack = new GameObject(this);
	resultBackSprite = resultBack->addComponent<GUISpriteRenderer>();
	resultBackSprite->setTextureByName("OptionBackGround");
	resultBackSprite->getTransform().setLocalPosition(Vec3{ 0,0,1.5f });
	resultBackSprite->getTransform().setLocalScale(Vec3{ 750,650,0.5f });

	//Sound
	pAudio = ClearObject->addComponent<AudioSource>();
	pAudio->setAudio("Endeng");

	pAudio->play(255);
	//SceneEffectƒIƒuƒWƒFƒNƒg¶¬
	pSceneEndEffect = new GameObject(this);
	m_pSceneEndEffect = pSceneEndEffect->addComponent<SceneEffect>();
	m_pSceneEndEffect->Initialize(1);
	pSceneStartEffect = new GameObject(this);
	m_pSceneStartEffect = pSceneStartEffect->addComponent<SceneEffect>();
	m_pSceneStartEffect->Initialize(0);
	m_pSceneStartEffect->StartEffect();
}

void ClearScene::update()
{
	ActiveLaptime();

	if (m_pSceneStartEffect->IsEnd())
	{
		if (GameDevice::getInput().isKeyDown(DIK_SPACE) ||
			ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START))
		{
			m_pSceneEndEffect->StartEffect();
		}
	}
}

void ClearScene::shutdown()
{
}

void ClearScene::SetSprite(GUISpriteRenderer* sprite[4][5][10])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sprite[i][j][0]->setTextureByName("num0");
			sprite[i][j][1]->setTextureByName("num1");
			sprite[i][j][2]->setTextureByName("num2");
			sprite[i][j][3]->setTextureByName("num3");
			sprite[i][j][4]->setTextureByName("num4");
			sprite[i][j][5]->setTextureByName("num5");
			sprite[i][j][6]->setTextureByName("num6");
			sprite[i][j][7]->setTextureByName("num7");
			sprite[i][j][8]->setTextureByName("num8");
			sprite[i][j][9]->setTextureByName("num9");
		}
	}
}

void ClearScene::ActiveLaptime()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				bool firstNum  = LapTime::GetResultTenThousand() == k;
				bool secondNum = LapTime::GetResultOneThousand() == k;
				bool thirdNum = LapTime::GetOneHundredPlace() == k;
				bool forthNum = LapTime::GetResultTen() == k;
				bool fifthNum = LapTime::GetResultOne() == k;

				bool firstNum1 = LapTime::GetResultTenThousand1() == k;
				bool secondNum1 = LapTime::GetResultOneThousand1() == k;
				bool thirdNum1 = LapTime::GetResultOneHundred1() == k;
				bool forthNum1 = LapTime::GetResultTen1() == k;
				bool fifthNum1 = LapTime::GetResultOne1() == k;

				bool firstNum3 = LapTime::GetResultTenThousand3() == k;
				bool secondNum3 = LapTime::GetResultOneThousand3() == k;
				bool thirdNum3 = LapTime::GetResultOneHundred3() == k;
				bool forthNum3 = LapTime::GetResultTen3() == k;
				bool fifthNum3 = LapTime::GetResultOne3() == k;

				resultContents.lapTimeSprite[0][0][k]->setActive(firstNum);
				resultContents.lapTimeSprite[0][1][k]->setActive(secondNum);
				resultContents.lapTimeSprite[0][2][k]->setActive(thirdNum);
				resultContents.lapTimeSprite[0][3][k]->setActive(forthNum);
				resultContents.lapTimeSprite[0][4][k]->setActive(fifthNum);

				resultContents.lapTimeSprite[1][0][k]->setActive(firstNum1);
				resultContents.lapTimeSprite[1][1][k]->setActive(secondNum1);
				resultContents.lapTimeSprite[1][2][k]->setActive(thirdNum1);
				resultContents.lapTimeSprite[1][3][k]->setActive(forthNum1);
				resultContents.lapTimeSprite[1][4][k]->setActive(fifthNum1);

				resultContents.lapTimeSprite[2][0][k]->setActive(firstNum3);
				resultContents.lapTimeSprite[2][1][k]->setActive(secondNum3);
				resultContents.lapTimeSprite[2][2][k]->setActive(thirdNum3);
				resultContents.lapTimeSprite[2][3][k]->setActive(forthNum3);
				resultContents.lapTimeSprite[2][4][k]->setActive(fifthNum3);
			}
		}
	}
}