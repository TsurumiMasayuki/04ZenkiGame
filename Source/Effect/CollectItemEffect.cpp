#include "CollectItemEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"
#include "Component/Item/CollectItem.h"

Action::CollectItemEffect::CollectItemEffect(ActionManager* actionManager)
{
}

void Action::CollectItemEffect::init()
{
	auto& random = GameDevice::getRandom();
	//エフェクト持続時間
	const float effectDuration = 1.0f;
	pObjParticle = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Cube"));

	for (int i = 0; i < 5; ++i)
	{	
		pObjParticle->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObjParticle->getTransform().setLocalScale(Vec3(0.4f));
		pRenderer = pObjParticle->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(2.0f, 2.0f, 2.0f, 1.0f));

		//ランダムな方向に移動+透明化
		pObjParticle->addComponent<Action::ActionManager>()->enqueueAction
		(
			new Spawn
			(
				{
					new EaseOutCubic(new MoveBy(Vec3(random.getRandom(-1.0f, 1.0f), random.getRandom(0.5f, 2.5f), random.getRandom(-0.5f, 0.5f)), 1.0f)),
					new ScaleTo(Vec3(0.0f, 0.0f, 0.0f),effectDuration),
					new ColorTo(Color(random.getRandom(1.5f,2.0f), 0.0, random.getRandom(0.0f,0.0f),1.0f), pRenderer, 0.5f)
				}
			)
		);

		pObjParticle->getComponent<Action::ActionManager>()->enqueueAction(new Destroy(0.0f));
	}
}

void Action::CollectItemEffect::update(float time)
{
}

void Action::CollectItemEffect::onSuspend()
{
}

Action::AbstractAction* Action::CollectItemEffect::clone()
{
	return nullptr;
}
