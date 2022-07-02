#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::onUpdate()
{
	if (GameInput::getInstance().getPlayerDash())
	{
		dash();
	}
	if (GameInput::getInstance().getSliding())
	{
		sliding();
	}

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
	if(!pAudio->isPlaying())play("Dash",0,0.1f);
}

void PlayerSound::sliding()
{
	play("Sliding", 0, 0.1f);
}
