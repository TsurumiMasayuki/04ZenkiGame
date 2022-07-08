#include "ZigzagEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include "Math/MathUtility.h"

void Zigzagenemy::onStart()
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

	wrapTimer.setMaxTime(3.0f);
}

void Zigzagenemy::onUpdate()
{
	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	// X����]���x�����W�A���ɕϊ�
	velocity.y = MathUtility::toRadian(velocity.y);

	// ��莞�Ԃŕ����]��
	if (wrapTimer.isTime())
	{
		wrap();
	}

	// �ړ��ʉ��Z
	Vec3 tmpVel = Vec3(velocity.x, velocity.y * dir, velocity.z);
	position += tmpVel * deltaTime;

	// �~�����W���f�J���g���W�n�ɕϊ�
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	getUser().getTransform().setLocalPosition(cartCoord);

	//��]
	getTransform().setLocalAngles(Vec3(0.0f, 0.0f, MathUtility::toDegree(position.y) + 180.0f));

	// �^�C�}�[�̍X�V
	wrapTimer.update();
}

void Zigzagenemy::init(Vec3 position, float speedY, float speedZ, float radius)
{
	// �����l�Z�b�g
	this->position = position;
	velocity = Vec3(0, speedY, speedZ);
	this->radius = radius;
}

void Zigzagenemy::wrap()
{
	// �ړ��������]
	dir = -dir;

	// �^�C�}�[���Z�b�g
	wrapTimer.reset();
}
