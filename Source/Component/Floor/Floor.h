#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"

class Floor
	: public AbstractComponent
{
public:
	// AbstractComponent ����Čp��
	virtual void onStart() override;
	virtual void onUpdate() override;
};

