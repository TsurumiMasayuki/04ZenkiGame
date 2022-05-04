#include "TestEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

void Action::TestEffect::init()
{
	auto& random = GameDevice::getRandom();

	//エフェクト用オブジェクトを10個生成
	for (int i = 0; i < 100; ++i)
	{
		auto pObj = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Sphere"), false);
		pObj->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObj->getTransform().setLocalScale(Vec3(0.05f));
		auto pRenderer = pObj->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(1.0f, 0.8f, 0.0f, 1.0f));

		//ランダムな方向に移動+透明化
		pObj->getActionManager().enqueueAction
		(
			new Spawn
			(
				{
					new EaseOutCubic(new MoveBy(Vec3(random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f)) * 1.1f, 1.0f)),
					new ColorTo(Color(1.0f, 1.0f, 1.0f, 0.0f), pRenderer, 1.0f)
				}
			)
		);

		pObj->getActionManager().enqueueAction(new Destroy(0.0f));
	}
}

void Action::TestEffect::update(float time)
{
}

void Action::TestEffect::onSuspend()
{
}

Action::AbstractAction* Action::TestEffect::clone()
{
    return new TestEffect();
}