#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Math/Vec3.h"

class Follow :
    public AbstractComponent
{
public:
	// AbstractComponent ‚ð‰î‚µ‚ÄŒp³
	virtual void onStart() override;
	virtual void onUpdate() override;

public:
	void SetGameObject(GameObject* gameObject) { pObj = gameObject; };
	void Setdistance(const Vec3 distance) { this->distance = distance; }

	GameObject* GetGameObject() { return pObj; }


private:

	GameObject* pObj;

	Vec3 distance;
};

