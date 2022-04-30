#pragma once
#include "C:\K019G1491\gamejam\inc\Component\Utility\Action\AbstractAction.h"

namespace Action
{
    class TestVibrationEffect
        : public AbstractAction
    {
        virtual void init() override;
        virtual void update(float time) override;
        virtual void onSuspend() override;
        virtual AbstractAction* clone() override;
    private:
        GameObject* m_pCameraObj;
    };
}