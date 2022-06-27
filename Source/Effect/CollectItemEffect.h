#pragma once
#include "Component/Utility/Action/AbstractAction.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Item/CollectItem.h"

namespace Action
{
    class CollectItemEffect :
        public AbstractAction
    {
        virtual void init() override;
        virtual void update(float time) override;
        virtual void onSuspend() override;
        virtual AbstractAction* clone() override;
    public:
        CollectItemEffect(ActionManager* actionManager);
    private:
        GameObject* pObjParticle;
        MeshRenderer* pRenderer;
        CollectItem* collectObj;
    };
}