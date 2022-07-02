#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/TimeLimitUi.h"
#include <vector>

class TimeLimitDraw :
    public AbstractComponent
{
public:
	//AbstractComponent ÇâÓÇµÇƒåpè≥
	virtual void onStart() override;
	virtual void onUpdate() override;

private:
	GUISpriteRenderer* numTexFirst[10];
	GUISpriteRenderer* numTexSecond[10];

	TimeLimitUi* GameObj;
	GameObject* objFirst[10];
	GameObject* objSecond[10];
};

