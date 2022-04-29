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
	for (int i = 0; i < 10; ++i)
	{
		//色をランダムで決定
		float color = random.getRandom(0.0f, 1.0f);
		//スケールをランダムで決定
		float scale = random.getRandom(5.0f, 15.0f);

		auto pObj = ModelGameObjectHelper::instantiateModel(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Cube"), false);
		pObj->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObj->getTransform().setLocalScale(Vec3(scale));
		auto pRenderer = pObj->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(color, color, color, 1.0f));

		//ランダムな方向に移動+透明化
		pObj->getActionManager().enqueueAction
		(
			new Spawn
			(
				{
					new EaseOutQuart(new MoveBy(Vec3(random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f)) * 25.0f, 1.0f)),
					new ColorTo(Color(color, color, color, 0.0f), pRenderer, 1.0f)
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
