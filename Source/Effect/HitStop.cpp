#include "HitStop.h"
#include "Device/GameDevice.h"

void HitStop::Start(float scale, float stopTime)
{
	// �^�C���X�P�[�����Z�b�g
	GameDevice::getGameTime().m_TimeScale = scale;

	// �f���^�^�C������̑�������
	stayTimer.setUseUnscaledTime(true);

	// �^�C�}�[�Z�b�g
	stayTimer.setMaxTime(stopTime);
	// �^�C�}�[�J�n
	stayTimer.reset();
}

void HitStop::update()
{
	// ��莞�ԂŌ��ɖ߂�
	if (stayTimer.isTime())
	{
		// �^�C���X�P�[�����Z�b�g
		GameDevice::getGameTime().m_TimeScale = 1.0f;
	}

	// �^�C�}�[�X�V
	stayTimer.update();
}
