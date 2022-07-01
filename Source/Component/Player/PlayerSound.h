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
    // AbstractComponent ����Čp��
    virtual void onStart() override;
    virtual void onUpdate() override;

    //�Đ��@����(Sound��,Loop��,���̑傫��)
    void play(const std::string& audioName, int loopCount = 0.0f, float volume = 1.0f);

    void dash();
    void sliding();
    void walk();
private:
    //�I�u�W�F�N�g�f�[�^
    GameObject* m_pSound;
    AudioSource* pAudio;
};

