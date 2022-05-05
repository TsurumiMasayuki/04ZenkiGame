#include "PlayerAttack.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/Camera.h"

#include "Component/Physics/BoxColliderBt.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

#include "Component/Player/PlayerStats.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

#include "Utility/JsonFileManager.h"

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

	//�������Ԃ��擾
	float m_TimeUntilDestroy = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats").m_FlameRemainTime;

	//���g��j��
	pActionManager->enqueueAction(new Action::Destroy(m_TimeUntilDestroy));

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
	m_pCameraActionManager->enqueueAction(new Action::EaseInBounce(new Action::RotateBy(Vec3(1.0f, 0.0f, 0.0f), 0.25f)));
	m_pCameraActionManager->enqueueAction(new Action::EaseInBounce(new Action::RotateBy(Vec3(-1.0f, 0.0f, 0.0f), 0.25f)));
}
