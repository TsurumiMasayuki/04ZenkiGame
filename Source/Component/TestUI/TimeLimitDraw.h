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

	void SetSprite(GUISpriteRenderer* sprite[3][10]);

private:
	GameObject* timeLimitObject[4][10];
	GUISpriteRenderer* timeLimitSprite[4][10];
	TimeLimitUi* GameObj;
};

