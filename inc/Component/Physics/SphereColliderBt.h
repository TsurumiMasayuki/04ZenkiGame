#pragma once
#include <Component/Physics/AbstractColliderBt.h>

class SphereColliderBt
	: public AbstractColliderBt
{
	// AbstractColliderBt を介して継承されました
	virtual void createCollisionShape() override;
};