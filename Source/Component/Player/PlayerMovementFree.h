#pragma once
#include "Component/Base/AbstractComponent.h"

#include "Utility/Timer.h"

#include "Component/Player/PlayerStats.h"

namespace Action
{
	class ActionManager;
}

class AudioSource;
class PlayerParamManager;

class PlayerMovementFree
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void init(PlayerParamManager* pPlayerParam);

private:
	//�ړ�
	void move(const Vec3& moveDir);

	//�_�b�V��
	void dash(const Vec3& moveDir);

private:
	PlayerParamManager* m_pPlayerParam;
	AudioSource* m_pAudioSource;
	PlayerStats m_Stats;
};