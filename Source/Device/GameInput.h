#pragma once
#include <Windows.h>
#include "Utility/SingletonTemplate.h"
#include <Math/Vec3.h>

class GameInput
	: public SingletonTemplate<GameInput>
{
public:
	friend class SingletonTemplate<GameInput>;

	// �ړ����b�N�ݒ�A�擾
	void setLock(bool _) { moveLock = _; }
	bool getLoack() { return moveLock; }

	// �ړ��擾
	Vec3 getPlayerMove();

	// �_�b�V���擾
	bool getPlayerWalk();

	// �_�b�V���擾
	bool getPlayerDash();

	//�_�b�V���X�^�[�g
	bool getPlayerDashStart();
	//�_�b�V���G���h
	bool getPlayerDashEND();

	//�X���C�f�B���O�擾
	bool getSliding();

	//�I�v�V�����擾
	bool getOption();

	//�I�v�V������I���擾
	bool getOptionSelectUp();

	//�I�v�V�������I���擾
	bool getOptionSelectDown();

protected:
	GameInput() {}
	~GameInput() {}

private:
	bool moveLock = false;	// �v���C���[�̈ړ����b�N

};