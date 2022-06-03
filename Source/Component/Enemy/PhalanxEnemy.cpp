#include "PhalanxEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

#include "Utility/ModelGameObjectHelper.h"

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
		float radRotateSpeed = MathUtility::toRadian(swingWidth * sinf(swingCnt - (10 / vec_object.size() * i)));

		Vec3 tmp_position = vec_object[i]->getTransform().getLocalPosition();
		tmp_position = CoordConverter::cartesianToCylinder(tmp_position);

		//�ړ�
		tmp_position.x = radius;	// x�͉~�����a�ŌŒ�
		tmp_position.y += radRotateSpeed * deltaTime;
		tmp_position.z += speedZ * deltaTime;	// z�͎w��X�s�[�h�Ői�� - �G���

		//�~�����W���f�J���g���W�ɕϊ�
		Vec3 cartCoord = CoordConverter::cylinderToCartesian(tmp_position);

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
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	// �z��̍č\�z
	vec_object.resize(length);

	// �G����
	for (int i = 0; i < length; i++)
	{
		// ����
		vec_object[i] = ModelGameObjectHelper::instantiateModel<int>(getUser().getGameMediator(), pCube);

		vec_object[i]->getTransform().setLocalPosition(position + Vec3(0, 0, i));
		vec_object[i]->addComponent<TestEnemy>()->init(0.0f, 0.0f);

		//��_�������\��
		if (i == mainUnit)
		{
			vec_object[i]->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		}
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
