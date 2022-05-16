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

	void setCylinderRadius(float radius);

private:
	//移動
	void move(const Vec3& moveDir);

	//ダッシュ
	void dash(const Vec3& moveDir);

	//円筒座標系から変換
	void convertCoord();

private:
	PlayerParamManager* m_pPlayerParam;
	AudioSource* m_pAudioSource;
	PlayerStats m_Stats;
	//円筒座標系
	Vec3 m_CylinderCoord;
};