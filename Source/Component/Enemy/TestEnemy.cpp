#include "TestEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

#include "btBulletDynamicsCommon.h"

void TestEnemy::onStart()
{
	m_CylinderCoord.z = getTransform().getLocalPosition().z;
	getUser().setTag("Enemy");
}

void TestEnemy::onUpdate()
{
	return;

	// ����W�擾
	Vec3 position = getUser().getTransform().getLocalPosition();

	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();
	//��]���x�����W�A���ɕϊ�
	float radRotateSpeed = MathUtility::toRadian(rotateSpeed);

	//�ړ�
	m_CylinderCoord.x = radius;
	m_CylinderCoord.y += radRotateSpeed * deltaTime;
	m_CylinderCoord.z += speed * deltaTime;

	//�~�����W���f�J���g���W�ɕϊ�
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(m_CylinderCoord);

	//���W��K�p
	getTransform().setLocalPosition(cartCoord);

	//��]
	getTransform().setLocalAngles(
		Vec3(0.0f,
			0.0f,
			MathUtility::toDegree(m_CylinderCoord.y))
	);
}

void TestEnemy::init(float speed, float rotateSpeed, float radius, Vec3 centerPoint)
{
	this->speed = speed;
	this->rotateSpeed = rotateSpeed;
	this->radius = radius;
	this->centerPoint = centerPoint;
}