#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
#include <vector>
#include "Component/Player/PlayerParamManager.h"
class TestUI
	:public AbstractComponent
{
public:
	//AbstractComponent ����Čp��
	virtual void onStart() override;
	virtual void onUpdate() override;

public:
	/// <summary>
	/// �̗͂�����
	/// </summary>
	/// <param name="health">�̗�</param>
	void SetHealth(float health) { this->health = health; }

	/// <summary>
	/// �ő�����x���猩�����݂̉����x�̊���������
	/// </summary>
	/// <param name="acceleration">�ő�����x���猩�����݂̉����x�̊���</param>
	void SetAcceleration(float acceleration) { this->acceleration = acceleration; }

	/// <summary>
	/// �R���̎c�ʂ�����
	/// </summary>
	/// <param name="fuel">�R���̎c��</param>
	void SetFuel(float fuel) { this->fuel = fuel; }

	/// <summary>
	/// �v���g�^�C�v�p�Q�[�W�ϐ��Ǘ��֐�
	/// </summary>
	/// <param name="health">�̗�</param>
	/// <param name="acceleration">�ő�����x���猩�����݂̉����x�̊���</param>
	/// <param name="fuel">�c�R��</param>
	void SetParam(float health, float acceleration, float fuel) { this->health = health; this->acceleration = acceleration;  this->fuel= fuel; }
	
private:
	//�eUI�̃f�[�^
	GameObject* healthGaugeObj = nullptr;
	GameObject* healthStocks[5];
	GameObject* healthStocksBlack[5];
	GameObject* accelerationGaugeObj = nullptr;
	GameObject* fuelGaugeObj = nullptr;
	GameObject* accelerationGaugeFlame = nullptr;
	GameObject* accelerationGaugeCore = nullptr;

	GUISpriteRenderer* healthStocksRenderer[5];
	GUISpriteRenderer* healthStocksBlackRenderer[5];
	GUISpriteRenderer* healthGuiSpriteRenderer=nullptr;
	GUISpriteRenderer* accelerationGuiSpriteRenderer = nullptr;
	GUISpriteRenderer* fuelGuiSpriteRenderer = nullptr;
	GUISpriteRenderer* accelerationGaugeFlameRenderer = nullptr;
	GUISpriteRenderer* accelerationGaugeCoreRenderer = nullptr;
	//UI�G�t�F�N�g
	GameObject* accelerationEffect = nullptr;
	GUISpriteRenderer* accelerationEffectSpriteRenderer = nullptr;
	std::vector<GameObject*> accEffect;
	std::vector<GUISpriteRenderer*>accEffectSpriteRenderer;
	//�eUI�̐��l
	//�ő�l
    float MAX_HEALTH = 5.0f;
    float MAX_ACCELERATION = 1.0f;
    float MAX_FUEL = 5.0f;
	//���ݒl
	float health;
	float fuel;
	//�������W
	Vec3 startHealthPos;
	Vec3 startAccelerationPos;
	Vec3 startFuelPos;
	//����
	float perHealth;
	float perAcceleration;
	float perFuel;
	//�摜�̃X�P�[��
	float healthGaugeScale;
	float accelerationGaugeScale;
	float fuelGaugeScale;
	//�����Q�[�W�v�Z�p�ϐ�
	float accAdjustNum = 180;

	//�����G�t�F�N�g
	float acceleration;
	GameObject* pPlayer = nullptr;
	GameObject* accEffectObj = nullptr;
	GUISpriteRenderer* accSprite = nullptr;
};

