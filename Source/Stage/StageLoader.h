#pragma once
#include "Stage/StageInfo.h"
#include "Component/Graphics/InstancedRenderer.h"

class IGameMediator;
class InstancingMaterial;

struct InstanceInfo
{
	DirectX::XMFLOAT4X4 m_InstanceMatrix;
	DirectX::XMFLOAT4 m_InstanceColor;
};

class StageLoader final
{
public:
	StageLoader(IGameMediator* pGameMediator);
	~StageLoader();

	//�X�e�[�W�̓ǂݍ���
	void loadStage(const StageInfo& stageInfo);

private:
	//�X�e�[�W�y��쐬
	void createStageBase(const StageInfo& stageInfo);

	//�I�u�W�F�N�g�쐬
	void createObjects(const StageInfo& stageInfo);

private:
	IGameMediator* m_pGameMediator;
	InstancingMaterial* m_pMaterial;
};