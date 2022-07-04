#include "BoundGimmick.h"
#include "Component/Physics/SphereColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void BoundGimmick::onStart()
{
	// �G�Ƃ��ă^�O�t��
	getUser().setTag("Enemy");

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

	changeTime.update();
}
