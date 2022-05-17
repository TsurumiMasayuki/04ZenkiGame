#include "TestFlameEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

Action::TestFlameEffect::TestFlameEffect(ActionManager* actionManager)
{
}

void Action::TestFlameEffect::init()
{	
	auto& random = GameDevice::getRandom();
	//エフェクト持続時間
	const float effectDuration = 1.0f;
	for (int i = 0; i < 15; ++i)
	{
		pObjParticle = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Cube"));
		pObjParticle->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObjParticle->getTransform().setLocalScale(Vec3(0.5f));
		pRenderer = pObjParticle->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(0.6f, 0.0f, 0.0f, 1.0f));

		//ランダムな方向に移動+透明化
		pObjParticle->addComponent<Action::ActionManager>()->enqueueAction
		(
			new Spawn
			(
				{
					new EaseOutCubic(new MoveBy(Vec3(random.getRandom(-0.5f, 0.5f), random.getRandom(0.0f, 1.0f), random.getRandom(-1.0f, -0.1f)), 1.0f)),
					new ScaleTo(Vec3(0.0f, 0.0f, 0.0f),effectDuration),
					new ColorTo(Color(1.0f, 0.0f, 0.0f, 1.0f), pRenderer, effectDuration)
				}
			)
		);

		pObjParticle->getComponent<Action::ActionManager>()->enqueueAction(new Destroy(0.0f));
	}
}

void Action::TestFlameEffect::update(float time)
{
}

void Action::TestFlameEffect::onSuspend()
{
}

Action::AbstractAction* Action::TestFlameEffect::clone()
{
    return nullptr;
}
