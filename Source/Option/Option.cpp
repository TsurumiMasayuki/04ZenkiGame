#include "Option.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

void Option::onStart()
{
	//オプション画面
	offOptionPos = Vec3{-800.0f,-800.0f,1.0f};
	onOptionPos = Vec3{ 0,-20,1.0f };
	optionScreenObj = new GameObject(getUser().getGameMediator());
	optionScreenObj->getTransform().setLocalPosition(Vec3{offOptionPos});
	optionScreenObj->getTransform().setLocalAngleZ(100);
	optionScreenSpriteRenderer = optionScreenObj->addComponent<GUISpriteRenderer>();
	optionScreenSpriteRenderer->setTextureByName("OptionBackGround");
	optionScreenObj->getTransform().setLocalScale(Vec3{ 600,600,1 });
	actionManager = optionScreenObj->addComponent<Action::ActionManager>();
	
	//選択ボタン
	for (float bottonNum = 0; bottonNum < 4; bottonNum++)
	{
		createBotton(bottonNum);
	}

	//現在選択しているボタン
	optionCurBottonObj = new GameObject(getUser().getGameMediator());
	optionCurBottonObj->getTransform().setLocalPosition(Vec3{ offBottonPos.at(options.size()-1)});
	optionCurBottonObj->getTransform().setLocalScale(Vec3{ 384,96,1 });
	optionCurBottonSpriteRenderer = optionCurBottonObj->addComponent<GUISpriteRenderer>();
	optionCurBottonSpriteRenderer->setTextureByName("OptionCurBotton");
	optionCurBottonSpriteRenderer->setColor({ 1,1,1,1 });

	isOption = false;
	count = 0;
	currentBottnNum = options.size();
	optionTimer.setMaxTime(1.0f);
}

void Option::onUpdate()
{
	optionTimer.update();

	//ゲーム進行を止める
	if (IsOption() && optionTimer.getCurrentTime() >= 1.0f)
	{
		GameDevice::getGameTime().m_TimeScale = 0.0f;
	}

	//オプション画面移動遷移
	if (!IsOption() && GameInput::getInstance().getOption() && optionTimer.isTime())
	{
		optionScreenObj->addComponent<Action::ActionManager>()->enqueueAction
		(
			new Action::Spawn
			(
				{
					new Action::EaseOutCubic(new Action::MoveTo(Vec3(onOptionPos),1.0f)),
					new Action::EaseOutCubic(new Action::RotateTo(Vec3(0.0f,0.0f,0.0f),1.0f))
				}
		    )
		);

		for (GameObject* optionBotton : options)
		{
			optionBotton->addComponent<Action::ActionManager>()->enqueueAction
		    (
		    	new Action::Spawn
		    	(
		    		{
						new Action::EaseOutCubic(new Action::MoveTo(Vec3(onBottonPos.at(count)),1.0f)),
		    		}
		    	)
		    );
			count++;
		}

		optionCurBottonObj->addComponent<Action::ActionManager>()->enqueueAction
		(
			new Action::Spawn
			(
				{
					new Action::EaseOutCubic(new Action::MoveTo(Vec3(onBottonPos.at(options.size() - 1).x,onBottonPos.at(options.size() - 1).y,onBottonPos.at(options.size() - 1).z - 0.1f),1.0f)),
				}
			)
		);
		
		if (optionTimer.isTime())
		{
			optionTimer.reset();
			isOption = !isOption;
			count = 0;
		}
	}//オプション中同じボタンでゲームに戻る
	else if(GameInput::getInstance().getOption() && optionTimer.isTime())
	{
		actionManager->enqueueAction(
			new Action::Spawn(
				{
					new Action::EaseInCubic(new Action::MoveTo(Vec3(offOptionPos),1.0f)),
					new Action::EaseInCubic(new Action::RotateTo(Vec3(0.0f,0.0f,100.0f),1.0f))
				}
			)
		);

		if (optionTimer.isTime())
		{
			optionCurBottonObj->getTransform().setLocalPosition(Vec3(offBottonPos.at(options.size()-1)));
		
			for (GameObject* optionBotton : options)
			{
				optionBotton->getTransform().setLocalPosition(Vec3(offBottonPos.at(count)));
				count++;
			}

			GameDevice::getGameTime().m_TimeScale = 1.0f;
			optionTimer.reset();
			isOption = !isOption;
			count = 0;
			currentBottnNum = options.size();
			currentBottnNum--;
		}
	}

	//現在選択ボタン移動
	if (IsOption() && GameInput::getInstance().getOptionSelectUp())
	{
		currentBottnNum++;

		if (currentBottnNum >= options.size())
		{
			currentBottnNum = 0;
		}

		optionCurBottonObj->getTransform().setLocalPosition(
			Vec3(onBottonPos.at(currentBottnNum).x, onBottonPos.at(currentBottnNum).y, onBottonPos.at(currentBottnNum).z - 0.1f));
	}
	else if (IsOption() && GameInput::getInstance().getOptionSelectDown())
	{
		currentBottnNum--;

		if (currentBottnNum < 0)
		{
			currentBottnNum = options.size();
			currentBottnNum--;
		}
		
		optionCurBottonObj->getTransform().setLocalPosition(
			Vec3(onBottonPos.at(currentBottnNum).x, onBottonPos.at(currentBottnNum).y, onBottonPos.at(currentBottnNum).z - 0.1f));
	}
}

void Option::createBotton(float bottonNum)
{
	GameObject* botton = new GameObject(getUser().getGameMediator());
	GUISpriteRenderer* bottonSprite = botton->addComponent<GUISpriteRenderer>();
	Vec3 bottonOffPos = Vec3{ -800.0f,-800.0f + (bottonNum * 100),0.9f };
	Vec3 bottonOnPos = Vec3{ 0,-200 + (bottonNum * 100) ,0.9f };

	botton->getTransform().setLocalScale(Vec3{ 384,96,1 });
	botton->getTransform().setLocalPosition(Vec3{bottonOffPos});
	bottonSprite->setTextureByName("OptionBotton");
	
	offBottonPos.push_back(bottonOffPos);
	onBottonPos.push_back(bottonOnPos);
	options.push_back(botton);
}