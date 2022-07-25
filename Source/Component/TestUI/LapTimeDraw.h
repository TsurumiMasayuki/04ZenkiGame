#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/TestUI/LapTime.h"
#include <vector>

class LapTimeDraw :
    public AbstractComponent
{
public:
	//AbstractComponent ÇâÓÇµÇƒåpè≥
	virtual void onStart() override;
	virtual void onUpdate() override;

	void SetSprite(GUISpriteRenderer* sprite[5][10]);

private:
	GameObject* lapTimeObject[5][10];
	GUISpriteRenderer* lapTimeSprite[5][10];
	GameObject* timeObject;
	GUISpriteRenderer* timeSprite;
	GameObject* pointObject;
	GUISpriteRenderer* pointSprite;
	GameObject* colonObject;
	GUISpriteRenderer* colonSprite;
	LapTime* GameObj;
};