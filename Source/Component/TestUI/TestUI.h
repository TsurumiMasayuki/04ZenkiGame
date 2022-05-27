#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include <vector>
class TestUI
	:public AbstractComponent
{
public:
	//AbstractComponent を介して継承
	virtual void onStart() override;
	virtual void onUpdate() override;

public:
	/// <summary>
	/// 体力を所得
	/// </summary>
	/// <param name="health">体力</param>
	void SetHealth(float health) { this->health = health; }

	/// <summary>
	/// 最大加速度から見た現在の加速度の割合を所得
	/// </summary>
	/// <param name="acceleration">最大加速度から見た現在の加速度の割合</param>
	void SetAcceleration(float acceleration) { this->acceleration = acceleration; }

	/// <summary>
	/// 燃料の残量を所得
	/// </summary>
	/// <param name="fuel">燃料の残数</param>
	void SetFuel(float fuel) { this->fuel = fuel; }

	/// <summary>
	/// プロトタイプ用ゲージ変数管理関数
	/// </summary>
	/// <param name="health">体力</param>
	/// <param name="acceleration">最大加速度から見た現在の加速度の割合</param>
	/// <param name="fuel">残燃料</param>
	void SetParam(float health, float acceleration, float fuel) { this->health = health; this->acceleration = acceleration;  this->fuel= fuel; }
	

private:
	//各UIのデータ
	GameObject* healthGaugeObj = nullptr;
	GameObject* healthStocks[5];
	GameObject* healthSticksBlack[5];
	GameObject* accelerationGaugeObj = nullptr;
	GameObject* fuelGaugeObj = nullptr;
	GameObject* accelerationGaugeFlame = nullptr;
	GameObject* accelerationGaugeCore = nullptr;

	GUISpriteRenderer* healthGuiSpriteRenderer=nullptr;
	GUISpriteRenderer* accelerationGuiSpriteRenderer = nullptr;
	GUISpriteRenderer* fuelGuiSpriteRenderer = nullptr;
	GUISpriteRenderer* accelerationGaugeFlameRenderer = nullptr;
	GUISpriteRenderer* accelerationGaugeCoreRenderer = nullptr;
	//UIエフェクト
	GameObject* accelerationEffect = nullptr;
	GUISpriteRenderer* accelerationEffectSpriteRenderer = nullptr;
	std::vector<GameObject*> accEffect;
	std::vector<GUISpriteRenderer*>accEffectSpriteRenderer;
	//各UIの数値
	//最大値
    float MAX_HEALTH = 5.0f;
    float MAX_ACCELERATION = 1.0f;
    float MAX_FUEL = 5.0f;
	//現在値
	float health;
	float acceleration;
	float fuel;
	//初期座標
	Vec3 startHealthPos;
	Vec3 startAccelerationPos;
	Vec3 startFuelPos;
	//割合
	float perHealth;
	float perAcceleration;
	float perFuel;
	//画像のスケール
	float healthGaugeScale;
	float accelerationGaugeScale;
	float fuelGaugeScale;
	//加速ゲージ計算用変数
	float accAdjustNum = 180;
};

