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
	void StartErase();
	bool FirstErase();
	bool SecondErase();
	bool ThirdErase();
	bool FourthErase();
	bool EraseIsEnd() { return endEraseFlg; }
	//�V�[���J�n����
	void StartEffect();
	bool FirstDraw();
	bool SecondDraw();
	bool ThirdDraw();
	bool FourthDraw();
	bool DrawIsEnd() { return endDrawFlg; }
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
	//���ʕϐ�
	const float VELOCITY = 40.0f;
	short callNum;
};