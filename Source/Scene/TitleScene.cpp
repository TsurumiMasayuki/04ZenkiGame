#include "TitleScene.h"

#include "Actor/Base/GameObject.h"
#include "Component/Graphics/D2DTextRenderer.h"
#include "Device/GameDevice.h"
#include "Device/ControllerInput.h"

std::string TitleScene::nextScene()
{
	return "Hoge";
}

bool TitleScene::isEnd()
{
	return GameDevice::getInput().isKeyDown(DIK_SPACE) ||
		ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START);
}

void TitleScene::start()
{
	/*auto pTitleTextObject = new GameObject(this);
	auto pTitleText = pTitleTextObject->addComponent<D2DTextRenderer>();
	pTitleText->setFont(L"Agency FB", L"ja-jp", 256.0f);
	pTitleText->setFontWeight(DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_MEDIUM);
	pTitleText->setFontStretch(DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL);
	pTitleText->setFontStyle(DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL);
	pTitleText->setTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
	pTitleText->setParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	pTitleText->setTextRect(0.0f, 0.0f, 1280.0f, 720.0f);
	pTitleText->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	pTitleText->setText(L"FLAME BOOTS");*/
	//オブジェクト生成
	titleObject = new GameObject(this);
	titleSprite = titleObject->addComponent<GUISpriteRenderer>();
	titleSprite->setTextureByName("title");
	titleObject->getTransform().setLocalPosition(Vec3{ 0,-50,2 });
	titleObject->getTransform().setLocalScale(Vec3{ 900,600,1 });
	titleSprite->setActive(true);

	titleBGObject = new GameObject(this);
	titleBGSprite = titleBGObject->addComponent<GUISpriteRenderer>();
	titleBGSprite->setTextureByName("titleBG");
	titleBGObject->getTransform().setLocalPosition(Vec3{ 0,0,2 });
	titleBGObject->getTransform().setLocalScale(Vec3{ 1280,720,2 });
	titleBGSprite->setActive(true);
	Random rand = GameDevice::getRandom();
	for (int i = 0; i < 100; i++)
	{
		currentLife[i] = 0;
		fireObjects[i] = new GameObject(this);
		fireSprites[i] = fireObjects[i]->addComponent<GUISpriteRenderer>();
		fireSprites[i]->setTextureByName("fire");
		
		float Xrand = rand.getRandom(-420.0f, 420.0f);
		float Yrand = rand.getRandom(-50.0f, 10.0f);
		float scaleRand = rand.getRandom(20.0f, 60.0f);
		float angleRand = rand.getRandom(0.0f, 360.0f);
		life[i] = rand.getRandom(80, 120);
		fireObjects[i]->getTransform().setLocalPosition(Vec3{ Xrand,Yrand,1 });
		fireObjects[i]->getTransform().setLocalScale(Vec3{ scaleRand,scaleRand,1 });
		fireObjects[i]->getTransform().setLocalAngles(Vec3{ 0,0,angleRand});
		fireSprites[i]->setColor(Color{ 255,1,1,0.6f });
		fireSprites[i]->setActive(true);
	}
	MainMove();
}

void TitleScene::update()
{
	for (int i = 0; i < 100; i++)
	{
		currentLife[i]++;
		Vec3 pos = fireObjects[i]->getTransform().getLocalPosition();
		fireObjects[i]->getTransform().setLocalPosition(Vec3{pos.x,pos.y+velocity[i],pos.z});
		if (currentLife[i] > life[i])
		{
			RePosition(i);
			MainMove();
			currentLife[i] = 0;
		}
	}
	SubMove();
	
}

void TitleScene::shutdown()
{
}

void TitleScene::SubMove()
{
	Random rand = GameDevice::getRandom();
	for (int i = 0; i < 100; i++)
	{
		float randomMove = rand.getRandom(-5.0f,5.0f);
		Vec3 pos = fireObjects[i]->getTransform().getLocalPosition();
		fireObjects[i]->getTransform().setLocalPosition(Vec3{pos.x+randomMove,pos.y,pos.z});
	}
}

void TitleScene::MainMove()
{

	
	for (int i = 0; i < 100; i++)
	{
		Random rand = GameDevice::getRandom();
		float randomMove = rand.getRandom(100, 300);
		Vec3 pos = fireObjects[i]->getTransform().getLocalPosition();
		float distance = Vec3::distance(pos, Vec3{ pos.x,pos.y+ randomMove,pos.z });
		velocity[i] = distance/life[i];
	}
}

void TitleScene::RePosition(int num)
{
	Random rand = GameDevice::getRandom();
	float Xrand = rand.getRandom(-420.0f, 420.0f);
	float Yrand = rand.getRandom(-50.0f, 10.0f);
	float scaleRand = rand.getRandom(20.0f, 60.0f);
	float angleRand = rand.getRandom(0.0f, 360.0f);
	life[num] = rand.getRandom(45, 120);
	fireObjects[num]->getTransform().setLocalPosition(Vec3{ Xrand,Yrand,1 });
	fireObjects[num]->getTransform().setLocalScale(Vec3{ scaleRand,scaleRand,1 });
	fireObjects[num]->getTransform().setLocalAngles(Vec3{ 0,0,angleRand });
}
