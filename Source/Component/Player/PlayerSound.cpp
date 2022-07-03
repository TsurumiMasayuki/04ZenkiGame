#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::onUpdate()
{
	//�_�b�V���g�p��
	if (GameInput::getInstance().getPlayerDash())
	{
		if(GameInput::getInstance().getPlayerDashStart())
			dash();
		//�X���C�f�B���O�g�p��
		if (GameInput::getInstance().getSliding())
			sliding();
	}
	if (GameInput::getInstance().getPlayerDashEND())
		pAudio->stop();
	//�ʏ�ړ�
	if (GameInput::getInstance().getPlayerWalk())
		walk();

}

void PlayerSound::play(const std::string& audioName, int loopCount, float volume)
{
	//Sound���ݒ�
	pAudio->setAudio(audioName);
	//���̑傫���ݒu
	pAudio->setVolume(volume);
	//�K��񐔂܂ōĐ�
	pAudio->play(loopCount);
}

void PlayerSound::dash()
{
	play("Dash",0,0.5f);
}

void PlayerSound::sliding()
{
	play("Sliding", 0, 0.5f);
}

void PlayerSound::walk()
{
	if (!pAudio->isPlaying())play("Walk", 0, 0.1f);
}
