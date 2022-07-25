#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Component/Utility/Action/AbstractAction.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Graphics/InstancedRenderer.h"
#include "Utility/InstancedRendererHelper.h"
#include "Component/Graphics/SpriteRenderer.h"

class IGameMediator;
class InstancingMaterial;

namespace Action
{
	class ActionManager;
}

struct InstancingInfo
{
	DirectX::XMFLOAT4X4 instancingMatrix;
	DirectX::XMFLOAT4   instancingColor;
};

class BackGround final : 
    public AbstractComponent 
{
public:
	// AbstractComponent ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onStart() override;
	virtual void onUpdate() override;

private:
	GameObject* backGrondObj[6];
	SpriteRenderer* backGroundSprite[6];
	MeshRenderer* backGroundMesh;

	GameObject* player;
	std::vector<InstancingInfo> inctanceInfo;
	GameObject* backGroundParticle[150];
	GameObject* instancedObj;
	InstancedRenderer<InstancingInfo>* instancedRenderer;
	InstancingMaterial* material;
};