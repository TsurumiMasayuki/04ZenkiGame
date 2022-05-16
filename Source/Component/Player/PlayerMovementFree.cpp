#include "PlayerMovementFree.h"

#include "Actor/Base/GameObject.h"

#include "Component/Audio/AudioSource.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerParamManager.h"

#include "Utility/JsonFileManager.h"

void PlayerMovementFree::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
}

void PlayerMovementFree::onUpdate()
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
		moveDir = Vec3(0.0f, 0.0f, 1.0f);
	//��
	if (input.isKey(DIK_DOWN))
		moveDir = Vec3(0.0f, 0.0f, -1.0f);
	//�E
	if (input.isKey(DIK_RIGHT))
		moveDir = Vec3(1.0f, 0.0f, 0.0f);
	//��
	if (input.isKey(DIK_LEFT))
		moveDir = Vec3(-1.0f, 0.0f, 0.0f);

	//�ړ��ʂ��[���Ȃ���s���Ȃ�
	if (moveDir.x == 0.0f && moveDir.z == 0.0f)
		return;

	dash(moveDir);
	move(moveDir);
}

void PlayerMovementFree::init(PlayerParamManager* pPlayerParam)
{
	m_pPlayerParam = pPlayerParam;
}

void PlayerMovementFree::move(const Vec3& moveDir)
{
	//�_�b�V���L�[��������Ă���Ȃ�I��
	if (GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//�ړ��ʂ��Z�o
	Vec3 move = moveDir * m_Stats.m_WalkSpeed * deltaTime;

	//���W�X�V
	getTransform().setLocalPosition(getTransform().getLocalPosition() + move);
}

void PlayerMovementFree::dash(const Vec3& moveDir)
{
	//�R�����[���Ȃ���s���Ȃ�
	if (m_pPlayerParam->isFuelZero())
		return;

	//�_�b�V���L�[��������Ă��Ȃ��Ȃ�I��
	if (!GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//�����x���擾
	float accel = 1.0f + m_pPlayerParam->getAcceleration();

	//deltaTime���擾
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//�ړ��ʂ��Z�o
	Vec3 move = moveDir * m_Stats.m_DashSpeed * accel * deltaTime;

	//���W�X�V
	getTransform().setLocalPosition(getTransform().getLocalPosition() + move);
}
