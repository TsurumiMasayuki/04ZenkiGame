#include "TestEnemy.h"
#include "Device/GameDevice.h"

void TestEnemy::onStart()
{
	// ���ꂼ����W������
	position = Vec3(0,0,0);
	speed = 1.0f;
	targetPos = Vec3(0,0,0);
}

void TestEnemy::onUpdate()
{
	// ����W�擾
	position = getUser().getTransform().getLocalPosition();

	// �ڕW���W�擾
	targetPos = object->getTransform().getLocalPosition();

	// �ړ������Z�o
	moveVec = targetPos - position;
	moveVec = moveVec.normalized();

	// ���W�X�V
	position += moveVec * speed * GameDevice::getGameTime().getDeltaTime();
	// ���W�Z�b�g
	getUser().getTransform().setLocalPosition(position);
}

void TestEnemy::SetTarget(GameObject* object)
{
	this->object = object;
}
