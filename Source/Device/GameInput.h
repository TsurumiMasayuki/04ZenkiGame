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
	bool getPlayerDash();

	//�X���C�f�B���O�擾
	bool getSliding();

protected:
	GameInput() {}
	~GameInput() {}

private:
	bool moveLock = false;	// �v���C���[�̈ړ����b�N

};