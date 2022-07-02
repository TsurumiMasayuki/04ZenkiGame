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

	// �R���C�_�[�t�^
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(true);
	// �d�̖͂�����
	x->setUseGravity(false);

	testTimer.setMaxTime(5.0f);

	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void TestEnemy::onUpdate()
{
	// ����ł������莞�Ԍ�ɑh��
	if (isDead && testTimer.isTime())
	{
		isDead = false;

		// �����蔻���ON
		getUser().getComponent<BoxColiiderBt>()->setActive(true);
	}

	// �^�C�}�[�̍X�V
	testTimer.update();

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

void TestEnemy::setDead(bool isDead)
{
	this->isDead = isDead;
	pAudio->setAudio("EnemyDown");

	pAudio->play();

	// �����蔻���OFF
	getUser().getComponent<BoxColiiderBt>()->setActive(false);

	testTimer.reset();
}
