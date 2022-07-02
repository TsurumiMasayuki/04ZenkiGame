#include "TestPlayerAttackedEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

Action::TestPlayerAttackedEffect::TestPlayerAttackedEffect(ActionManager* actionManager)
	: cameraShakeStrengthFirst(2.0f, 0.0f, 2.0f),
	cameraShakeStrengthSecond(0.0f, 0.0f, 0.0f)
{
}

void Action::TestPlayerAttackedEffect::init()
{
	//m_pCameraObj->getActionManager().enqueueAction(new Action::EaseInOutBounce(new Action::RotateTo(cameraShakeStrengthFirst, 1.0f)));
	//m_pCameraObj->getActionManager().enqueueAction(new Action::EaseInOutBounce(new Action::RotateTo(cameraShakeStrengthSecond, 1.0f)));

	//auto& random = GameDevice::getRandom();

	////エフェクト用オブジェクトを100個生成
	//for (int i = 0; i < 100; ++i)
	//{
	//	pObjParticle = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Sphere"), false);
	//	pObjParticle->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
	//	pObjParticle->getTransform().setLocalScale(Vec3(0.05f));
	//	pRenderer = pObjParticle->getChildren().at(0)->getComponent<MeshRenderer>();
	//	pRenderer->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	//	//ランダムな方向に移動
	//	pObjParticle->getActionManager().enqueueAction
	//	(
	//		new Spawn
	//		(
	//			{
	//				new EaseOutCubic(new MoveBy(Vec3(random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f)) * 1.1f, 1.0f)),
	//			}
	//		)
	//	);

	//	pObjParticle->getActionManager().enqueueAction(new Destroy(0.0f));
	//}
}

void Action::TestPlayerAttackedEffect::update(float time)
{
}

void Action::TestPlayerAttackedEffect::onSuspend()
{
}

Action::AbstractAction* Action::TestPlayerAttackedEffect::clone()
{
	return nullptr;
}