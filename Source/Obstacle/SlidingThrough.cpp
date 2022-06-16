#include "SlidingThrough.h"
#include "Actor/Base/GameObject.h"
#include "Device/GameDevice.h"
#include "Device/GameInput.h"
#include "Device/ControllerInput.h"
#include "Utility/ModelGameObjectHelper.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"
#include "Component/Physics/BoxColliderBt.h"
#include "btBulletDynamicsCommon.h"

void SlidingThrough::onStart()
{
	// �R���C�_�[�t�^
	auto collider = getUser().addComponent<BoxColiiderBt>();
	collider->setTrigger(true);
	// �d�̖͂�����
	collider->setUseGravity(false);
	o_Timer.setMaxTime(1.0f);
}

void SlidingThrough::onUpdate()
{
	o_Timer.update();
	//���͂��擾
	auto& gameInput = GameInput::getInstance();
	
	if (gameInput.getPlayerDash() && gameInput.getSliding() && o_Timer.isTime())
	{
		o_Timer.reset();
		 //�����蔻���ON
		getUser().getComponent<BoxColiiderBt>()->setActive(false);
    }

	if (o_Timer.isTime())
	{
		//�R���C�_�[�𖳌���
		if (getUser().getComponent<BoxColiiderBt>()->isActive() == false)
			getUser().getComponent<BoxColiiderBt>()->setActive(true);
	}
}

void SlidingThrough::onTriggerEnter(GameObject* pHit)
{

}
