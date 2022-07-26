#include "TitleScene.h"

#include "Actor/Base/GameObject.h"
#include "Component/Graphics/D2DTextRenderer.h"
#include "Device/GameDevice.h"
#include "Device/ControllerInput.h"
#include "Component/Audio/AudioSource.h"


std::string TitleScene::nextScene()
{
	return "Hoge";
}

bool TitleScene::isEnd()
{
	return m_pSceneEffect->IsEnd();
}

void TitleScene::start()
{
	//SceneEffectオブジェクト生成
	pSceneEffect = new GameObject(this);
	m_pSceneEffect = pSceneEffect->addComponent<SceneEffect>();
	m_pSceneEffect->Initialize(1);
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

	//Sound関連
	//Sound関連用Object生成
	GameObject* m_pSound = new GameObject(this);
	auto pAudio = m_pSound->addComponent<AudioSource>();
	//各種データ設定
	pAudio->setAudio("Title");
	pAudio->setVolume(0.1f);
	//再生
	pAudio->play(255);

	//オブジェクト生成
	titleObject = new GameObject(this);
	titleObject->getTransform().setLocalPosition(Vec3{ 0,-50,3 });
	titleObject->getTransform().setLocalScale(Vec3{ 900,600,1 });
	titleSprite = titleObject->addComponent<GUISpriteRenderer>();
	titleSprite->setTextureByName("title");
	titleSprite->setActive(true);
	
	titleBGObject = new GameObject(this);
	titleBGObject->getTransform().setLocalPosition(Vec3{ 0,0,5 });
	titleBGObject->getTransform().setLocalScale(Vec3{ 1280,720,5});
	titleBGSprite = titleBGObject->addComponent<GUISpriteRenderer>();
	titleBGSprite->setTextureByName("titleBG");
	titleBGSprite->setActive(true);

	GameObject* pButtom = new GameObject(this);
	pButtom->getTransform().setLocalPosition(Vec3{ -200,-200,1 });
	pButtom->getTransform().setLocalScale(Vec3{ 100,100,1 });
	GUISpriteRenderer* pButtomSprite = nullptr;
	pButtomSprite = pButtom ->addComponent<GUISpriteRenderer>();
	pButtomSprite->setTextureByName("buttom");
	pButtomSprite->setActive(true);

	GameObject* pStart = new GameObject(this);
	pStart->getTransform().setLocalPosition(Vec3{ 0,-200,1 });
	pStart->getTransform().setLocalScale(Vec3{ 300,100,1 });
	GUISpriteRenderer* pStratSprite = nullptr;
	pButtomSprite = pStart->addComponent<GUISpriteRenderer>();
	pButtomSprite->setTextureByName("start");
	pButtomSprite->setActive(true);


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
		fireObjects[i]->getTransform().setLocalPosition(Vec3{ Xrand,Yrand,3 });
		fireObjects[i]->getTransform().setLocalScale(Vec3{ scaleRand,scaleRand,1 });
		fireObjects[i]->getTransform().setLocalAngles(Vec3{ 0,0,angleRand});
		fireSprites[i]->setColor(Color{ 255,1,1,0.6f });
		fireSprites[i]->setActive(true);
	}
	MainMove();
}

void TitleScene::update()
{
	if (GameDevice::getInput().isKeyDown(DIK_SPACE) ||
		ControllerInput::getInstance().isPadButtonDown(ControllerInput::PAD_BUTTON::START))
	{
		m_pSceneEffect->StartEffect();
	}
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
	fireObjects[num]->getTransform().setLocalPosition(Vec3{ Xrand,Yrand,4 });
	fireObjects[num]->getTransform().setLocalScale(Vec3{ scaleRand,scaleRand,4 });
	fireObjects[num]->getTransform().setLocalAngles(Vec3{ 0,0,angleRand });
}
