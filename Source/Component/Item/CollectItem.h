#pragma once
#include "Component/Item/CollectItem.h"
#include "Component/Base/AbstractComponent.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Utility/Timer.h"
#include "CollectItemUI.h"

namespace Action
{
    class ActionManager;
}

//当たり判定部分
class CollectItemUI;
class CollectItem :
    public AbstractComponent
{
public:
    virtual void onStart() override;
    virtual void onUpdate() override;
    virtual void onTriggerEnter(GameObject* pHit) override;
private:
    GameObject* GameObj;
    CollectItemUI* CollectItemUIObj;
    Action::ActionManager* m_pActionManager;
};