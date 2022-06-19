#pragma once
#include "Component/Item/CollectItem.h"
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Utility/Timer.h"
#include "CollectItemUI.h"

class CollectItemUI;
class CollectItem :
    public AbstractComponent
{
public:
    virtual void onStart() override;
    virtual void onUpdate() override;
    virtual void onTriggerEnter(GameObject* pHit) override;

    bool  SetDead(bool flag) { return isDead = flag; }
    bool& IsDead() { return isDead; }
private:
    bool isDead;
    CollectItemUI* ItemUi;
};

