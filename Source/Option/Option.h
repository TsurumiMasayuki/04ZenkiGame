#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Utility/Timer.h"
#include <vector>

namespace Action
{
	class ActionManager;
}

class Option
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void createBotton(float bottonNum);
	//オプション中かどうか
	bool IsOption() { return isOption; }
private:
	//オプションオブジェクト
	GameObject* optionScreenObj = nullptr;
	GUISpriteRenderer* optionScreenSpriteRenderer = nullptr;
	GameObject* optionCurBottonObj = nullptr;
	GUISpriteRenderer* optionCurBottonSpriteRenderer = nullptr;
	std::vector<GameObject*> options;
	Action::ActionManager* actionManager;
	Timer optionTimer;
	Vec3 offOptionPos;
	Vec3 onOptionPos;
	std::vector<Vec3> offBottonPos;
	std::vector<Vec3> onBottonPos;

	int currentBottnNum;
	int count;
	bool isOption;//オプション中かどうか
};