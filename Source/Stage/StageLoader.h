#pragma once
#include "Stage/StageInfo.h"

class IGameMediator;

class StageLoader final
{
public:
	StageLoader(IGameMediator* pGameMediator);

	//ステージの読み込み
	void loadStage(const StageInfo& stageInfo);

private:
	//ステージ土台作成
	void createStageBase(const StageInfo& stageInfo);

	//オブジェクト作成
	void createObjects(const StageInfo& stageInfo);

private:
	IGameMediator* m_pGameMediator;
};