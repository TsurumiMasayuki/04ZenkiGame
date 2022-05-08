#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"

class Floor
	: public AbstractComponent
{
public:
	// AbstractComponent ‚ğ‰î‚µ‚ÄŒp³
	virtual void onStart() override;
	virtual void onUpdate() override;
};

