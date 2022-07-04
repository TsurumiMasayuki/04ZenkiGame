#include "BarrierEnemy.h"
#include "Component/Physics/SphereColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void BarrierEnemy::onStart()
{
	// ����W�擾
	position = getUser().getTransform().getLocalPosition();
	rotation = getUser().getTransform().getLocalAngles();

	// �G�Ƃ��ă^�O�t��
	getUser().setTag("Enemy");

	// �R���C�_�[�t�^
	auto x = getUser().addComponent<SphereColliderBt>();
	x->setTrigger(false);
	// �d�̖͂�����
	x->setUseGravity(false);

}

void BarrierEnemy::onUpdate()
{
	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	// X����]���x�����W�A���ɕϊ�
	velocity.y = MathUtility::toRadian(velocity.y);

	// �ړ��ʉ��Z
	position += velocity * deltaTime;

	// �~�����W���f�J���g���W�n�ɕϊ�
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	getUser().getTransform().setLocalPosition(cartCoord);
}

void BarrierEnemy::init(Vec3 position, float speedZ, float speedY, float radius)
{
	this->position = position;
	velocity.y = speedY;
	velocity.z = speedZ;
	this->radius = radius;
}
