#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::play(std::string& audioName, int loopCount, float volume)
{
	//Sound���ݒ�
	pAudio->setAudio(audioName);
	//���̑傫���ݒu
	pAudio->setVolume(volume);
	//�K��񐔂܂ōĐ�
	pAudio->play(loopCount);
}
