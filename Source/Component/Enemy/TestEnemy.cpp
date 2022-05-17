#include "TestEnemy.h"
#include "Device/GameDevice.h"

void TestEnemy::onStart()
{
}

void TestEnemy::onUpdate()
{
	// ����W�擾
	position = getUser().getTransform().getLocalPosition();



	// ���W�X�V
	position += moveVec * speed * GameDevice::getGameTime().getDeltaTime();
	// ���W�Z�b�g
	getUser().getTransform().setLocalPosition(position);
}

void TestEnemy::init(float angle, float speed = 1.0f, float radius = 11.0f, Vec3 centerPoint = Vec3(0, 0, 0))
{
	this->angle = angle;
	this->speed = speed;
	this->rasius = radius;
	this->centerPoint = centerPoint;
}