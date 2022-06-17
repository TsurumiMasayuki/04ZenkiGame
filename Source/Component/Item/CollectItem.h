#pragma once
#include "Component/Item/CollectItem.h"
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Utility/Timer.h"

class CollectItem :
    public AbstractComponent
{
public:
    virtual void onStart() override;
    virtual void onUpdate() override;
    virtual void onTriggerEnter(GameObject* pHit) override;

    bool  SetDead(bool flag) { return isDead = flag; }
    bool  GetDead() { return isDead; }

private:
    Timer o_Timer;
    GameObject* itemObj;
    GUISpriteRenderer* CollectItemRenderer;
    std::vector<Vec3> offPos;
    std::vector<Vec3> onPos;
    float count;
    bool isDead;
};

