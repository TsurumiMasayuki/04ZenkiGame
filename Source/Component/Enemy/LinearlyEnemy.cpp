#include "LinearlyEnemy.h"
#include "Device/GameDevice.h"

void LinearlyEnemy::onStart()
{
	// ���ꂼ����W������
	position = Vec3(0, 0, 0);
	speed = 1.0f;
	targetPos = Vec3(0, 0, 0);

	moveTimer.setMaxTime(3.0f);
	easingTimer.setMaxTime(1.0f);
}

void LinearlyEnemy::onUpdate()
{
	// ����W�擾
	position = getUser().getTransform().getLocalPosition();

	// �ڕW���W�擾
	targetPos = object->getTransform().getLocalPosition();

	// �ړ���
	if (canMove)
	{
		// ���W�X�V
		position += moveVec * speed * GameDevice::getGameTime().getDeltaTime();
		// ���W�Z�b�g
		getUser().getTransform().setLocalPosition(position);
	}
	// ��~��
	else
	{
		// �������Ȃ�
	}
	
	// �ړ��A��~�̐؂�ւ�
	if (moveTimer.isTime())
	{
		canMove = !canMove;

		if (canMove)
		{
			moveTimer.setMaxTime(moveTime);
			moveTimer.reset();
		}
		else
		{
			moveTimer.setMaxTime(stopTime);
			moveTimer.reset();
		}
	}

	moveTimer.update();
}

void LinearlyEnemy::SetTarget(GameObject* object)
{
	this->object = object;
}

Vec3 LinearlyEnemy::DecideDir()
{
	// �ړ������Z�o
	Vec3 result = targetPos - position;
	result.normalized();
	return result;
}
