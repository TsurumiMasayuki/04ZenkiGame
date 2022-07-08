#include "PressEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

void PressEnemy::onStart()
{
	// ����W�擾
	Vec3 position = getUser().getTransform().getLocalPosition();

	// �G�Ƃ��ă^�O�t��
	getUser().setTag("Enemy");

	// �R���C�_�[�t�^
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(false);
	// �d�̖͂�����
	x->setUseGravity(false);

}

void PressEnemy::onUpdate()
{
	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	// X����]���x�����W�A���ɕϊ�
	velocity.y = MathUtility::toRadian(velocity.y);

	if (targetObj)
	{
		Vec3 targetPos = targetObj->getTransform().getLocalPosition();

		if (targetPos.distance(position) < 5.0f)
		{
			press();
		}
	}

	// ���~���㏸
	if (isPress && position.x)
	{
		velocity.x = -3.0f * deltaTime;
	}
	else
	{
		velocity.x = 1.0f * deltaTime;
	}

	// �ړ��ʉ��Z
	Vec3 tmpVel = Vec3(velocity.x, velocity.y, velocity.z);
	position += tmpVel * deltaTime;

	// �~�����W���f�J���g���W�n�ɕϊ�
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	getUser().getTransform().setLocalPosition(cartCoord);

	//��]
	getTransform().setLocalAngles(Vec3(0.0f, 0.0f, MathUtility::toDegree(position.y) + 180.0f));

}

void PressEnemy::init(Vec3 position, float speedY, float speedZ, float radius)
{
	// �����l�Z�b�g
	this->position = Vec3(position.x + 5.0f, position.y, position.z);
	velocity = Vec3(0, speedY, speedZ);
	this->radius = radius;
}

void PressEnemy::press()
{
	isPress = !isPress;
}
