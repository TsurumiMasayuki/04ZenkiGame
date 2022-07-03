#include "TestPlayerAttackedEffect.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

Action::TestPlayerAttackedEffect::TestPlayerAttackedEffect(ActionManager* actionManager)
	: cameraShakeStrengthFirst(1.0f, 0.0f, 0.0f),
	cameraShakeStrengthSecond(-1.0f, 0.0f, 0.0f)
{
}

void Action::TestPlayerAttackedEffect::init()
{
	auto& random = GameDevice::getRandom();

	float x = random.getRandom(-10.0f, 10.0f);
	float y = random.getRandom(-10.0f, 10.0f);

	m_pCameraObj = &m_pUser->getGameMediator()->getMainCamera()->getUser();
	auto pCameraAction = m_pCameraObj->getComponent<Action::ActionManager>();
	pCameraAction->enqueueAction(new Action::EaseInOutBounce(new Action::MoveBy(Vec3(x, y, 0.0f), 0.1f)));
	pCameraAction->enqueueAction(new Action::EaseInOutBounce(new Action::MoveBy(Vec3(-x, -y, 0.0f), 0.1f)));

	return;

	//�G�t�F�N�g�p�I�u�W�F�N�g��100����
	for (int i = 0; i < 10; ++i)
	{
		pObjParticle = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Sphere"), false);
		pObjParticle->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObjParticle->getTransform().setLocalScale(Vec3(0.05f));
		pRenderer = pObjParticle->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

		//�����_���ȕ����Ɉړ�
		pObjParticle->addComponent<Action::ActionManager>()->enqueueAction
		(
			new Spawn
			(
				{
					new EaseOutCubic(new MoveBy(Vec3(random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f), random.getRandom(-1.0f, 1.0f)) * 1.1f, 1.0f)),
				}
				)
		);

		pObjParticle->getComponent<Action::ActionManager>()->enqueueAction(new Destroy(0.0f));
	}
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