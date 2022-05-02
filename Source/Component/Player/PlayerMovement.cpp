#include "PlayerMovement.h"
#include "Actor/Base/GameObject.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

using namespace Action;

void PlayerMovement::onStart()
{
	m_pActionManager = getUser().addComponent<ActionManager>();

	m_DashElapsedTime = 0.0f;
	m_DashMaxTime = 3.0f;
}

void PlayerMovement::onUpdate()
{
	//���̓f�o�C�X���擾
	const auto& input = GameDevice::getInput();

	//�ړ�����
	Vec3 moveDir = Vec3::zero();

	//���͂ɉ����Ĉړ��������Z�b�g(�}�X�ڂȂ̂Ŏ΂߈ړ��͂Ȃ�)
	//��
	if (input.isKey(DIK_UP))
		moveDir = Vec3(0.0f, 1.0f, 0.0f);
	//��
	if (input.isKey(DIK_DOWN))
		moveDir = Vec3(0.0f, -1.0f, 0.0f);
	//�E
	if (input.isKey(DIK_RIGHT))
		moveDir = Vec3(1.0f, 0.0f, 0.0f);
	//��
	if (input.isKey(DIK_LEFT))
		moveDir = Vec3(-1.0f, 0.0f, 0.0f);

	//�ړ��ʂ��[���Ȃ���s���Ȃ�
	if (moveDir.x == 0.0f && moveDir.y == 0.0f)
	{
		//�_�b�V���o�ߎ��Ԃ��[���ɂ���
		m_DashElapsedTime = 0.0f;
		return;
	}

	dash(moveDir);
	move(moveDir);
}

void PlayerMovement::move(const Vec3& moveDir)
{
	//�_�b�V���L�[��������Ă���Ȃ�I��
	if (GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//�A�j���[�V�����̓r���Ȃ�I��
	if (m_pActionManager->actionCount() > 0)
		return;

	//1�}�X�ړ�
	m_pActionManager->enqueueAction(new EaseOutCubic(new MoveBy(moveDir, 0.25f)));
}

void PlayerMovement::dash(const Vec3& moveDir)
{
	//�f���^�^�C�����擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//�_�b�V���L�[��������Ă���Ȃ�ړ����x����
	if (GameDevice::getInput().isKey(DIK_SPACE))
	{
		m_DashElapsedTime += deltaTime;
	}

	//�_�b�V���L�[��������Ă��Ȃ��Ȃ�I��
	if (!GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//�A�j���[�V�����̓r���Ȃ�I��
	if (m_pActionManager->actionCount() > 0)
		return;

	const Vec3& position = getUser().getTransform().getLocalPosition();
	m_pActionManager->enqueueAction(new MoveBy(moveDir, 0.25f * std::fmaxf(0.0f, 1.0f - m_DashElapsedTime / m_DashMaxTime)));

	return;
}
