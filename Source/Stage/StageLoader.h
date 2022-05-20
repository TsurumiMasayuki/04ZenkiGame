#pragma once
#include "Stage/StageInfo.h"

class IGameMediator;

class StageLoader final
{
public:
	StageLoader(IGameMediator* pGameMediator);

	//�X�e�[�W�̓ǂݍ���
	void loadStage(const StageInfo& stageInfo);

private:
	//�X�e�[�W�y��쐬
	void createStageBase(const StageInfo& stageInfo);

	//�I�u�W�F�N�g�쐬
	void createObjects(const StageInfo& stageInfo);

private:
	IGameMediator* m_pGameMediator;
};