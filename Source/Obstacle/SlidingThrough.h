#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Utility/Timer.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Physics/BoxColliderBt.h"
#include "btBulletDynamicsCommon.h"

//�X���C�f�B���O���ʂ���Q��
class SlidingThrough :
    public AbstractComponent
{
public:
    virtual void onStart() override;
    virtual void onUpdate() override;
    virtual void onTriggerEnter(GameObject* pHit) override;

private:
    Timer o_Timer;
    MeshRenderer* Renderer;
};

