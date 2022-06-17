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

	//ステージの読み込み
	void loadStage(const StageInfo& stageInfo);

private:
	//ステージ土台作成
	void createStageBase(const StageInfo& stageInfo);

	//オブジェクト作成
	void createObjects(const StageInfo& stageInfo);

private:
	IGameMediator* m_pGameMediator;
	InstancingMaterial* m_pMaterial;
};