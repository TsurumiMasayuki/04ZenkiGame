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
	bool getPlayerDash();

protected:
	GameInput() {}
	~GameInput() {}

private:
	bool moveLock = false;	// プレイヤーの移動ロック

};