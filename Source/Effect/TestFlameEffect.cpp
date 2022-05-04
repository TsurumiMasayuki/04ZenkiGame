#include "TestFlameEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

void Action::TestFlameEffect::init()
{
	auto& random = GameDevice::getRandom();
	const float interval = 0.4f;

	//エフェクト用オブジェクトを10個生成
	for (int i = 0; i < 10; ++i)
	{
		auto pObj = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Cube"));
		pObj->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObj->getTransform().setLocalScale(Vec3(0.3f,0.3f,0.3f));
		auto pRenderer = pObj->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

		//直線
		pObj->getActionManager().enqueueAction
		(
			new Spawn
			(
				{
					new EaseInSine(new MoveBy(Vec3(0, i, i) * -interval, 1.0f)),
					new ColorTo(Color(1.0f,0.0f, 0.0f, 0.0f), pRenderer, 1.0f)
				}
			)
		);

		pObj->getActionManager().enqueueAction(new Destroy(0.0f));
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
    return new TestFlameEffect;
}