#include "PlayerMovement.h"
#include "Actor/Base/GameObject.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

#include "Component/Player/PlayerAttack.h"

#include "Utility/JsonFileManager.h"

using namespace Action;

void PlayerMovement::onStart()
{
	m_pActionManager = getUser().addComponent<ActionManager>();

	m_DashElapsedTime = 0.0f;
	m_DashMaxTime = 3.0f;

	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
}

void PlayerMovement::onUpdate()
{
	//���̓f�o�C�X���擾
	const auto& input = GameDevice::getInput();

	//�ݒ�t�@�C�����z�b�g�����[�h
	if (input.isKeyDown(DIK_R))
	{
		m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
	}

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
	m_pActionManager->enqueueAction(new EaseOutCubic(new MoveBy(moveDir, m_Stats.m_WalkTime)));
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

	//�ړ����Ԃ̊������Z�o
	float moveTimeRatio = std::fmaxf(0.0f, 1.0f - m_DashElapsedTime / m_DashMaxTime);

	const Vec3& position = getUser().getTransform().getLocalPosition();

	//�ړ�
	m_pActionManager->enqueueAction(new MoveBy(moveDir, m_Stats.m_DashTime * moveTimeRatio));

	//�U���p�I�u�W�F�N�g�𐶐�
	auto pAttackObject = new GameObject(getUser().getGameMediator());
	//���g�̍��W��ݒ�
	pAttackObject->getTransform().setLocalPosition(getUser().getTransform().getLocalPosition());
	//�U���p�R���|�[�l���g���A�^�b�`
	pAttackObject->addComponent<PlayerAttack>();

	return;
}
