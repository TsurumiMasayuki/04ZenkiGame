#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::play(std::string& audioName, int loopCount, float volume)
{
	//Sound–¼Ý’è
	pAudio->setAudio(audioName);
	//‰¹‚Ì‘å‚«‚³Ý’u
	pAudio->setVolume(volume);
	//‹K’è‰ñ”‚Ü‚ÅÄ¶
	pAudio->play(loopCount);
}
