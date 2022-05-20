#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Math/Vec3.h"
class DistanceActivater :
    public AbstractComponent
{
public:
	// AbstractComponent ‚ð‰î‚µ‚ÄŒp³
	virtual void onStart() override;
	virtual void onUpdate() override;

public:
	void SetGameObject(GameObject* gameObject) { pObj = gameObject; }
	void SetPlayer(GameObject* player) { this->player = player; }
	void SetActivationPos(float z){ activationPos=z; }

	GameObject* GetGameObject() { return pObj; }


private:

	GameObject* player;
	GameObject* pObj;
	float activationPos;

};

