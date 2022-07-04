#include "BoundGimmick.h"
#include "Component/Physics/SphereColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>
#include "Component/Player/PlayerParamManager.h"

void BoundGimmick::onStart()
{
	// �M�~�b�N�Ƃ��ă^�O�t��
	getUser().setTag("Gimmick");

	// �R���C�_�[�t�^
	auto x = getUser().addComponent<SphereColliderBt>();
	x->setTrigger(false);
	// �d�̖͂�����
	x->setUseGravity(false);

	changeTime.setMaxTime(3.0f);
}

void BoundGimmick::onUpdate()
{
	// ���Ԃ�������؂�ւ���
	if (changeTime.isTime())
	{
		isExpansion = !isExpansion;
	}

	// �c���
	if (isExpansion)
	{
		scale = Vec3(3, 3, 3);
	}
	else
	{
		scale = Vec3(1, 1, 1);
	}

	// ���˕Ԃ�
	if (getUser().getTransform().getLocalPosition().distance(targetObj->getTransform().getLocalPosition()) < scale.x)
	{
		// �ړ��������]
		Vec3 pMoveDir = targetObj->getComponent<PlayerParamManager>()->getMoveDir();
		targetObj->getComponent<PlayerParamManager>()->setMoveDir(-pMoveDir);
	}

	// �T�C�Y�Z�b�g
	getUser().getTransform().setLocalScale(scale);

	changeTime.update();
}
