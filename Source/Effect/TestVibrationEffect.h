#pragma once
#include "Component/Utility/Action/AbstractAction.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Math/Vec3.h"

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
        TestVibrationEffect(ActionManager* actionManager);
    private:
        //カメラの揺れの強さ(1回目)
        Vec3 cameraShakeStrengthFirst;
        //カメラの揺れの強さ(2回目)
        Vec3 cameraShakeStrengthSecond;

        Action::ActionManager* actionManager;
    };
}