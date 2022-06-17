#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Component/Graphics/MeshRenderer.h"
class GoalObject : public AbstractComponent {
public:
	// AbstractComponent ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onStart() override;
	virtual void onUpdate() override;

	void Initialize(Vec3 goalPos, GameObject* player);
private:
	GameObject* pPlayer = nullptr;
	GameObject* goalObj = nullptr;
	GUISpriteRenderer* goalObjSprite = nullptr;
	GameObject* goal = nullptr;
	const float GOAL_DISTANCE = 3.0f;
};