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
        void setCamera(GameObject* pCameraObj) { m_pCameraObj = pCameraObj; }
    private:
        GameObject* m_pCameraObj;
        //ƒJƒƒ‰‚Ì—h‚ê‚Ì‹­‚³(1‰ñ–Ú)
        Vec3 cameraShakeStrengthFirst;
        //ƒJƒƒ‰‚Ì—h‚ê‚Ì‹­‚³(2‰ñ–Ú)
        Vec3 cameraShakeStrengthSecond;
    };
}