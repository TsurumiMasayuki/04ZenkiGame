#include "JumpingEnemy.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void JumpingEnemy::onStart()
{
	cylinderCoord.z = getTransform().getLocalPosition().z;
	getUser().setTag("Enemy");

	// �R���C�_�[�t�^
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(true);
	// �d�̖͂�����
	x->setUseGravity(false);

	intervalTimer.setMaxTime(interval);
}

void JumpingEnemy::onUpdate()
{
	// ����W�擾
	Vec3 position = getUser().getTransform().getLocalPosition();

	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//��]���x�����W�A���ɕϊ�
	float radRotateSpeed = MathUtility::toRadian(velocity.y);

	// �~�����W�ϊ�
	position = CoordConverter::cartesianToCylinder(position);

	// �W�����v������
	float jumpVec = sinf(cycleCnt);
	// �}�C�i�X�ɂȂ�����0�ɋ����ϊ�
	if (jumpVec <= 0)
	{
		jumpVec = 0;
	}

	// ���W�Z�b�g
	position.x = radius + jumpVec * 3;
	position.y += radRotateSpeed * deltaTime;
	position.z += velocity.z * deltaTime;	// z�͎w��X�s�[�h�Ői��

	//�~�����W���f�J���g���W�ɕϊ�
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(position);

	//���W��K�p
	getUser().getTransform().setLocalPosition(cartCoord);

	// 
	cycleCnt += deltaTime;

	// �^�C�}�[�̍X�V
	intervalTimer.update();
}

void JumpingEnemy::init(Vec3 position, float speedZ, float speedY, float radius)
{
	// �������W�Z�b�g
	getUser().getTransform().setLocalPosition(position);

	// ���x�Z�b�g
	velocity.y = speedY;
	velocity.z = speedZ;

	// �~�����a�Z�b�g
	this->radius = radius;
}

void JumpingEnemy::setJumpParameter(float hight, float interval)
{
	this->hight = hight;
	this->interval = interval;

	intervalTimer.setMaxTime(interval);
}
