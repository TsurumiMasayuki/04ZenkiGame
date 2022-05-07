#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

namespace Action
{
	class ActionManager;
}

class AudioSource;

//�v���C���[//�U������p�R���|�[�l���g
class PlayerAttack
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

protected:
	virtual void onCollisionEnter(GameObject* pHit) override;

private:
	//�J�����ɃA�^�b�`����Ă���ActionManager
	Action::ActionManager* m_pCameraActionManager;

	//�_���[�W�p����
	AudioSource* m_pAudioSource;
};