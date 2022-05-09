#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "Utility/SingletonTemplate.h"

struct StickInput
{
	float x;
	float y;
};

struct DPadInput
{
	int x;
	int y;
};

class ControllerInput
	: public SingletonTemplate<ControllerInput>
{
public:
	//コントローラーのボタン指定用Enum
	enum class PAD_BUTTON
	{
		X = 0x4000,		//Xボタン
		Y = 0x8000,		//Yボタン
		A = 0x1000,		//Aボタン
		B = 0x2000,		//Bボタン
		LB = 0x0100,	//Lボタン
		RB = 0x0200,	//Rボタン
		START = 0x0010,	//Startボタン
		BACK = 0x0020	//Backボタン
	};

	enum class PAD_TRIGGER
	{
		LEFT,
		RIGHT
	};

	friend class SingletonTemplate<ControllerInput>;

	void update();

	//コントローラーのボタンが押し続けれているか判定
	bool isPadButton(PAD_BUTTON button) const;
	//コントローラーのボタンが離された瞬間か判定
	bool isPadButtonUp(PAD_BUTTON button) const;
	//コントローラーのボタンが押された瞬間か判定
	bool isPadButtonDown(PAD_BUTTON button) const;

	//左スティックの入力を取得
	StickInput getLStickInput() const;
	//右スティックの入力を取得
	StickInput getRStickInput() const;

	//十字ボタンの入力を取得
	DPadInput getDPadInput() const;

	//コントローラーのボタンが押し続けれているか判定
	bool isTrigger(PAD_TRIGGER trigger) const;
	//コントローラーのボタンが離された瞬間か判定
	bool isTriggerUp(PAD_TRIGGER trigger) const;
	//コントローラーのボタンが押された瞬間か判定
	bool isTriggerDown(PAD_TRIGGER trigger) const;

protected:
	//コンストラクタを隠す
	ControllerInput() {};
	//デストラクタを隠す
	virtual ~ControllerInput() {};

private:
	//コントローラーが接続されているか
	bool m_IsPadConnected;

	//現在のフレームのコントローラー情報
	XINPUT_STATE m_CurPadInfo;
	//一つ前のフレームのコントローラー情報
	XINPUT_STATE m_PrePadInfo;
};