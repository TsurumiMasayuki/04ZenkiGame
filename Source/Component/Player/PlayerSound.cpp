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
	//Sound–¼Ý’è
	pAudio->setAudio(audioName);
	//‰¹‚Ì‘å‚«‚³Ý’u
	pAudio->setVolume(volume);
	//‹K’è‰ñ”‚Ü‚ÅÄ¶
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
