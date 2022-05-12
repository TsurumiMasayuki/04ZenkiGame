#include "TestVibrationEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

Action::TestVibrationEffect::TestVibrationEffect(ActionManager* actionManager)
    : cameraShakeStrengthFirst(2.0f,0.0f,2.0f),
    cameraShakeStrengthSecond(0.0f,0.0f,0.0f)
{
}

void Action::TestVibrationEffect::init()
{
    m_pCameraObj->getActionManager().enqueueAction(new Action::EaseInOutBounce(new Action::RotateTo(cameraShakeStrengthFirst, 1.0f)));
    m_pCameraObj->getActionManager().enqueueAction(new Action::EaseInOutBounce(new Action::RotateTo(cameraShakeStrengthSecond, 1.0f)));
}

void Action::TestVibrationEffect::update(float time)
{
}

void Action::TestVibrationEffect::onSuspend()
{
}

Action::AbstractAction* Action::TestVibrationEffect::clone()
{
    return nullptr;
}

