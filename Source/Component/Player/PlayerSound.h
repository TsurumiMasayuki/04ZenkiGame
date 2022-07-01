#pragma once
#include <string>

#include "Component/Base/AbstractComponent.h"
#include "Component/Audio/AudioSource.h"
#include "Actor/Base/GameObject.h"
#include "Device/GameInput.h"

class PlayerSound :
    public AbstractComponent
{
public:
    // AbstractComponent を介して継承
    virtual void onStart() override;
    virtual void onUpdate() override;

    //再生　引数(Sound名,Loop回数,音の大きさ)
    void play(const std::string& audioName, int loopCount = 0.0f, float volume = 1.0f);

    void dash();
    void sliding();
    void walk();
private:
    //オブジェクトデータ
    GameObject* m_pSound;
    AudioSource* pAudio;
};

