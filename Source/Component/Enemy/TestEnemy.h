#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Actor/Base/GameObject.h"
#include "Component/Audio/AudioSource.h"
#include "Utility/Timer.h"

class TestEnemy
	: public AbstractComponent
{
public:
	// AbstractComponent を介して継承
	virtual void onStart() override;
	virtual void onUpdate() override;

public:

	void init(float speed, float rotateSpeed, float radius = 11.0f, Vec3 centerPoint = Vec3(0, 0, 0));

	void setCenter(Vec3 centerPoint) { this->centerPoint = centerPoint; }

	void setRadius(float radius) { this->radius = radius; }

	/// <summary>
	/// 速度セット
	/// </summary>
	/// <param name="speed">速度</param>
	void setSpeed(float speed) { this->speed = speed; }

	/// <summary>
	/// 速度取得
	/// </summary>
	/// <returns>速度</returns>
	float getspeed() { return speed; }

	/// <summary>
	/// 生き死に設定
	/// </summary>
	/// <param name="isDead">生き死に</param>
	void setDead(bool isDead);

	/// <summary>
	/// 生き死に取得
	/// </summary>
	/// <returns>生き死に</returns>
	bool getDead() { return isDead; }

private:
	//速度
	float speed;
	//回転速度
	float rotateSpeed;

	// ステージ情報
	float radius = 0.0f;
	Vec3 centerPoint = Vec3(0, 0, 0);

	Vec3 m_CylinderCoord;

	bool isDead = false;

	Timer testTimer;
	GameObject* m_pSound;
	AudioSource* pAudio;
};
