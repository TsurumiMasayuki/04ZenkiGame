#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"

class SceneEffect :public AbstractComponent
{
public:
	//AbstractComponent ����Čp��
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="callNum">�Ăяo������ 0-�V�[���J�n 1-�V�[���I��</param>
	void Initialize(short callNum);
	//�V�[���I������
	bool FirstErase();
	bool SecondErase();
	bool ThirdErase();
	bool FourthErase();
	//�V�[���J�n����
	bool FirstDraw();
	bool SecondDraw();
	bool ThirdDraw();
	bool FourthDraw();
	bool TimerDraw();
	void TimerISActive(bool timerIsActive) { this->timerIsActive = timerIsActive;}
	//���ʏ���
	void StartEffect();
	bool IsEnd();
private:
	//�V�[���I�������p�ϐ�
	GameObject* eraseObject;
	GUISpriteRenderer* eraseSprite;
	GameObject* maskObject[4];
	GUISpriteRenderer* maskSprite[4];
	bool startFlg = false;
	bool firstRePosFlg = false;
	bool secondRePosFlg = false;
	bool thirdRePosFlg = false;
	bool fourthRePosFlg = false;
	bool firstEndFlg = false;
	bool secondEndFlg = false;
	bool thirdEndFlg = false;
	bool fourthEndFlg = false;
	float totalVelocity[4];
	Vec3 erasePos;
	Vec3 maskStartPos[4];
	Vec3 maskPos[4];
	bool endEraseFlg = false;
	//�V�[���J�n�����p�ϐ�
	GameObject* drawObject;
	GUISpriteRenderer* drawSprite;
	GameObject* drawMaskObj[4];
	GUISpriteRenderer* drawMaskSprite[4];
	
	bool drawStartFlg = false;
	bool drawFirstRePosFlg = false;
	bool drawSecondRePosFlg = false;
	bool drawThirdRePosFlg = false;
	bool drawFourthRePosFlg = false;
	bool drawFirstEndFlg = false;
	bool drawSecondEndFlg = false;
	bool drawThirdEndFlg = false;
	bool drawFourthEndFlg = false;
	float drawTotalVelocity[4];
	Vec3 drawPos;
	Vec3 drawMaskStartPos[4];
	Vec3 drawMaskPos[4];
	bool endDrawFlg = false;
	//�Q�[���X�^�[�g�����o
	GameObject* timeObject[3];
	GUISpriteRenderer* timeSprite[3];
	GameObject* startObject;
	GUISpriteRenderer* startSprite;
	short count;
	bool prog[3];
	bool timerIsActive;
	//���ʕϐ�
	const float VELOCITY = 40.0f;
	short callNum;
};