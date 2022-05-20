#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Math/Vec3.h"
class DistanceActivater :
    public AbstractComponent
{
public:
	// AbstractComponent ÇâÓÇµÇƒåpè≥
	virtual void onStart() override;
	virtual void onUpdate(GameObject* player) override;

public:
	void SetGameObject(GameObject* gameObject) { pObj = gameObject; }
	void SetActivationPos(float z){ activationPos=z; }

	GameObject* GetGameObject() { return pObj; }


private:

	GameObject* pObj;
	float activationPos;

};

