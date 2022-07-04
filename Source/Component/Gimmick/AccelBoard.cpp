#include "AccelBoard.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>
#include "Component/Player/PlayerParamManager.h"

void AccelBoad::onStart()
{
	// �M�~�b�N�Ƃ��ă^�O�t��
	getUser().setTag("Gimmick");

	// �R���C�_�[�t�^
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(false);
	// �d�̖͂�����
	x->setUseGravity(false);

	// ���̂��Ȃ���
	getUser().getComponent<BoxColiiderBt>()->setTrigger(true);

	activeTimer.setMaxTime(3.0f);
}

void AccelBoad::onUpdate()
{
	Vec3 scale = getUser().getTransform().getLocalScale();
	Vec3 position = getUser().getTransform().getLocalPosition();
	Vec3 pPosition = targetObj->getTransform().getLocalPosition();

	// ����������
	if (!interval)
	{
		if (position.x - scale.x / 2 >= pPosition.x + 0.5f && position.x + scale.x / 2 >= pPosition.x - 0.5f &&
			position.y - scale.y / 2 >= pPosition.y + 0.5f && position.y + scale.y / 2 >= pPosition.y - 0.5f &&
			position.z - scale.z / 2 >= pPosition.z + 0.5f && position.z + scale.z / 2 >= pPosition.z - 0.5f)
		{
			// �ړ��ʕω�
			float pMoveSpeed = targetObj->getComponent<PlayerParamManager>()->getMoveSpeed();
			// ���x�����ȂȂ甼���܂ŉ���
			targetObj->getComponent<PlayerParamManager>()->setMoveSpeed(pMoveSpeed * acceleration);

			// �ꎞ�x�~
			interval = true;

			// �x�~�^�C�}�[�J�n
			activeTimer.reset();
		}
	}

	// ���Ԃ��o������߂�
	if (activeTimer.isTime())
	{
		interval = true;
	}

	// �^�C�}�[�̍X�V
	activeTimer.update();
}
