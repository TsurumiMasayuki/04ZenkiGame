#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
class GoalObject : public AbstractComponent {
public:
	// AbstractComponent ����Čp������܂���
	virtual void onStart() override;
	virtual void onUpdate() override;

	void Initialize(float Zpos, GameObject* player);
private:
	GameObject* goalPos = nullptr;
	GameObject* pPlayer = nullptr;
	GameObject* goalObj = nullptr;
	GUISpriteRenderer* goalObjSprite = nullptr;
};