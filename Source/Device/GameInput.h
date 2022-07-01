#pragma once
#include <Windows.h>
#include "Utility/SingletonTemplate.h"
#include <Math/Vec3.h>

class GameInput
	: public SingletonTemplate<GameInput>
{
public:
	friend class SingletonTemplate<GameInput>;

	// 移動ロック設定、取得
	void setLock(bool _) { moveLock = _; }
	bool getLoack() { return moveLock; }

	// 移動取得
	Vec3 getPlayerMove();

	// ダッシュ取得
	bool getPlayerWalk();

	// ダッシュ取得
	bool getPlayerDash();

	//ダッシュスタート
	bool getPlayerDashStart();
	//ダッシュエンド
	bool getPlayerDashEND();

	//スライディング取得
	bool getSliding();

	//オプション取得
	bool getOption();

	//オプション上選択取得
	bool getOptionSelectUp();

	//オプション下選択取得
	bool getOptionSelectDown();

protected:
	GameInput() {}
	~GameInput() {}

private:
	bool moveLock = false;	// プレイヤーの移動ロック

};