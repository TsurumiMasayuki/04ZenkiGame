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

	//�G�t�F�N�g�p�I�u�W�F�N�g��10����
	for (int i = 0; i < 10; ++i)
	{
		//�F�������_���Ō���
		float color = random.getRandom(0.0f, 1.0f);
		//�X�P�[���������_���Ō���
		float scale = random.getRandom(5.0f, 15.0f);

		auto pObj = ModelGameObjectHelper::instantiateModel<int>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Cube"), false);
		pObj->getTransform().setLocalPosition(m_pUser->getTransform().getLocalPosition());
		pObj->getTransform().setLocalScale(Vec3(scale));
		auto pRenderer = pObj->getChildren().at(0)->getComponent<MeshRenderer>();
		pRenderer->setColor(Color(color, color, color, 1.0f));

		//�����_���ȕ����Ɉړ�+������
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