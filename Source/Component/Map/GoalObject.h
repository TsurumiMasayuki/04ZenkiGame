#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Audio/AudioSource.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Component/Graphics/MeshRenderer.h"

class GoalObject : public AbstractComponent {
public:
	// AbstractComponent を介して継承されました
	virtual void onStart() override;
	virtual void onUpdate() override;

	void Initialize(Vec3 goalPos, GameObject* player);
	bool GetIsGoal();
private:
	GameObject* pPlayer = nullptr;
	GameObject* goalObj = nullptr;
	AudioSource* pAudio =nullptr;
	GUISpriteRenderer* goalObjSprite = nullptr;
	GameObject* goal = nullptr;
	const float GOAL_DISTANCE = 3.0f;
	bool isGoal;
	float velocity;
	std::vector<Transform*> goalEffects;
	bool isSound;
};