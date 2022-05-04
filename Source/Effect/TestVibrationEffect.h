#pragma once
#include "Component/Utility/Action/AbstractAction.h"

namespace Action
{
    class TestVibrationEffect
        : public AbstractAction
    {
    protected:
        virtual void init() override;
        virtual void update(float time) override;
        virtual void onSuspend() override;
        virtual AbstractAction* clone() override;
    public:
        void setCamera(GameObject* pCameraObj) { m_pCameraObj = pCameraObj; }
    private:
        GameObject* m_pCameraObj;
    };
}