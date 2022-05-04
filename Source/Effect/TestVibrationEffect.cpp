#include "TestVibrationEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

void Action::TestVibrationEffect::init()
{
    //ƒJƒƒ‰‚ð—h‚ç‚·
    m_pCameraObj->getActionManager().enqueueAction(new Action::EaseInBounce(new Action::RotateTo(Vec3(1.0f, 0.0f, 0.0f), 0.5f)));
    m_pCameraObj->getActionManager().enqueueAction(new Action::EaseInBounce(new Action::RotateTo(Vec3(1.0f, 0.0f, 0.0f), 0.5f)));
}

void Action::TestVibrationEffect::update(float time)
{
}

void Action::TestVibrationEffect::onSuspend()
{
}

Action::AbstractAction* Action::TestVibrationEffect::clone()
{
    return new TestVibrationEffect;
}