#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"

//UI•”•ª
class CollectItemUI
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	static int&  GetCount()  
	{ 
		return count; 
	}

	static void AddCount(int& value) 
	{
		value += 1;
	}

	bool  SetDead(bool flag) { return isDead = flag; }
	
	bool& IsDead() { return isDead; }

private:
	float maxCount;
	GameObject* itemObj[3];
	GUISpriteRenderer* CollectItemRenderer[3];
	static int  count;
	bool isDead;
};