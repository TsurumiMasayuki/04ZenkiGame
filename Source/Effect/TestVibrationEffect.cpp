#include "TestVibrationEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

Action::TestVibrationEffect::TestVibrationEffect(ActionManager* actionManager)
	: cameraShakeStrengthFirst(1.0f, 0.0f, 0.0f),
	cameraShakeStrengthSecond(-1.0f, 0.0f, 0.0f),
	actionManager(actionManager)
{
}

void Action::TestVibrationEffect::init()
{
	actionManager->enqueueAction(new Action::EaseInOutBounce(new Action::RotateBy(cameraShakeStrengthFirst, 0.1f)));
	actionManager->enqueueAction(new Action::EaseInOutBounce(new Action::RotateBy(cameraShakeStrengthSecond, 0.1f)));
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

