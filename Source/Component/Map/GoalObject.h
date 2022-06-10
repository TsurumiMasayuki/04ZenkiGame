#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
class GoalObject : public AbstractComponent {
public:
	// AbstractComponent ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onStart() override;
	virtual void onUpdate() override;

	void Initialize(float Zpos, GameObject* player);
private:
	GameObject* goalPos = nullptr;
	GameObject* m_pPlayer = nullptr;
	GameObject* goalObj = nullptr;
	GUISpriteRenderer* goalObjSprite = nullptr;
};