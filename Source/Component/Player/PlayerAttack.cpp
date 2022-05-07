#include "PlayerAttack.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/Camera.h"

#include "Component/Physics/BoxColliderBt.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"
#include "Effect/TestEffect.h"

void PlayerAttack::onStart()
{
	//���g�ɃR���C�_�[���A�^�b�`
	auto pBoxCollider = getUser().addComponent<BoxColiiderBt>();
	pBoxCollider->setMass(1.0f);
	pBoxCollider->setTrigger(true);
	pBoxCollider->setUseGravity(false);

	//���g��ActionManager���A�^�b�`
	auto pActionManager = getUser().addComponent<Action::ActionManager>();
	//�Ή��G�t�F�N�g�����s
	pActionManager->enqueueAction(new Action::TestFlameEffect());
	//���g��j��
	pActionManager->enqueueAction(new Action::Destroy(3.0f));

	//�J�������A�^�b�`����Ă���I�u�W�F�N�g���擾
	auto pCameraObject = &getUser().getGameMediator()->getMainCamera()->getUser();

	//ActionManager���擾
	m_pCameraActionManager = pCameraObject->getComponent<Action::ActionManager>();
}

void PlayerAttack::onUpdate()
{
}

void PlayerAttack::onCollisionEnter(GameObject* pHit)
{
	//�G�łȂ��Ȃ�return
	if (!pHit->compareTag("Enemy")) 
		return;

	if (m_pCameraActionManager->actionCount() > 0) 
		return;

	//�J������h�炷
	m_pCameraActionManager->enqueueAction(new Action::EaseInBounce(new Action::RotateBy(Vec3(1.0f, 0.0f, 0.0f), 0.5f)));
	m_pCameraActionManager->enqueueAction(new Action::EaseInBounce(new Action::RotateBy(Vec3(-1.0f, 0.0f, 0.0f), 0.5f)));
}
