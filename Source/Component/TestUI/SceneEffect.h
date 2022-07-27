#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"

class SceneEffect :public AbstractComponent
{
public:
	//AbstractComponent を介して継承
	virtual void onStart() override;
	virtual void onUpdate() override;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="callNum">呼び出す処理 0-シーン開始 1-シーン終了</param>
	void Initialize(short callNum);
	//シーン終了処理
	bool FirstErase();
	bool SecondErase();
	bool ThirdErase();
	bool FourthErase();
	//シーン開始処理
	bool FirstDraw();
	bool SecondDraw();
	bool ThirdDraw();
	bool FourthDraw();
	bool TimerDraw();
	void TimerISActive(bool timerIsActive) { this->timerIsActive = timerIsActive;}
	//共通処理
	void StartEffect();
	bool IsEnd();
private:
	//シーン終了処理用変数
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
	//シーン開始処理用変数
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
	//ゲームスタート時演出
	GameObject* timeObject[3];
	GUISpriteRenderer* timeSprite[3];
	GameObject* startObject;
	GUISpriteRenderer* startSprite;
	short count;
	bool prog[3];
	bool timerIsActive;
	//共通変数
	const float VELOCITY = 40.0f;
	short callNum;
};