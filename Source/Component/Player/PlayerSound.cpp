#include "PlayerSound.h"

void PlayerSound::onStart()
{
	m_pSound = new GameObject(getUser().getGameMediator());
	pAudio = m_pSound->addComponent<AudioSource>();
}

void PlayerSound::onUpdate()
{
	//スライディング使用時
	if (GameInput::getInstance().getSliding())
	{
		sliding();
	}

	//通常移動
	if (GameInput::getInstance().getPlayerWalk())
	{
		walk();
	}

}

void PlayerSound::play(const std::string& audioName, int loopCount, float volume)
{
	//Sound名設定
	pAudio->setAudio(audioName);
	//音の大きさ設置
	pAudio->setVolume(volume);
	//規定回数まで再生
	pAudio->play(loopCount);
}

void PlayerSound::dash()
{
	play("Dash", 0, 0.5f);
}

void PlayerSound::sliding()
{
	play("Sliding", 0, 0.5f);
}

void PlayerSound::walk()
{
	if (!pAudio->isPlaying()) play("Walk", 0, 0.1f);
}
