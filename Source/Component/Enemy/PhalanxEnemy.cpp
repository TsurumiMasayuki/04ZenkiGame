#include "PhalanxEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

void PhalanxEnemy::onStart()
{

}

void PhalanxEnemy::onUpdate()
{
	// ����W�擾
	//Vec3 position = vec_object[i]->getTransform().getLocalPosition();

	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	for (int i = 0; i < vec_object.size(); i++)
	{
		//��]���x�����W�A���ɕϊ�
		float radRotateSpeed = MathUtility::toRadian(swingWidth * sinf(swingCnt - (1 / vec_object.size() * i)));

		//�ړ�
		cylinderCoord.x = radius;	// x�͉~�����a�ŌŒ�
		cylinderCoord.y += radRotateSpeed * deltaTime;
		cylinderCoord.z += speedZ * deltaTime - (float)i * 1.0f;	// z�͎w��X�s�[�h�Ői�� - �G���

		//�~�����W���f�J���g���W�ɕϊ�
		Vec3 cartCoord = CoordConverter::cylinderToCartesian(cylinderCoord);

		//���W��K�p
		vec_object[i]->getTransform().setLocalPosition(cartCoord);

		//��]
		vec_object[i]->getTransform().setLocalAngles(
			Vec3(0.0f,
				0.0f,
				MathUtility::toDegree(cylinderCoord.y))
		);
	}

	// �{�̂����񂾂�
	if (vec_object[mainUnit]->getComponent<TestEnemy>()->getDead())
	{
		// �S���E��
		for (auto x : vec_object)
		{
			x->getComponent<TestEnemy>()->setDead(true);
			//x->setActive(false);
		}
	}

	// �����p
	swingCnt += deltaTime;
}

void PhalanxEnemy::init(Vec3 position, int length, int mainUnit, float radius, float speedZ)
{
	// �z��̍č\�z
	vec_object.resize(length);

	// �G����
	for (int i = 0; i < length; i++)
	{
		// ����
		vec_object[i] = new GameObject(getUser().getGameMediator());
	}

	// �{�̔ԍ��Z�b�g
	if (mainUnit < length - 1)
	{
		this->mainUnit = mainUnit;
	}
	else
	{
		this->mainUnit = length - 1;
	}
	
	// �~���̔��a�Z�b�g
	this->radius = radius;

	// ���x�Z�b�g
	this->speedZ = speedZ;
}
