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
	auto pTitleTextObject = new GameObject(this);
	auto pTitleText = pTitleTextObject->addComponent<D2DTextRenderer>();
	pTitleText->setFont(L"Agency FB", L"ja-jp", 256.0f);
	pTitleText->setFontWeight(DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_MEDIUM);
	pTitleText->setFontStretch(DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL);
	pTitleText->setFontStyle(DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL);
	pTitleText->setTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
	pTitleText->setParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	pTitleText->setTextRect(0.0f, 0.0f, 1280.0f, 720.0f);
	pTitleText->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	pTitleText->setText(L"FLAME BOOTS");
}

void TitleScene::update()
{
}

void TitleScene::shutdown()
{
}
