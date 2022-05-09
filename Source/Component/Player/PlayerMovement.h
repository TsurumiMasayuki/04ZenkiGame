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

class PlayerMovement
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void init(PlayerParamManager* pPlayerParam);

private:
	//移動
	void move(const Vec3& moveDir);

	//ダッシュ
	void dash(const Vec3& moveDir);

private:
	PlayerParamManager* m_pPlayerParam;

	Action::ActionManager* m_pActionManager;

	AudioSource* m_pAudioSource;

	PlayerStats m_Stats;
};