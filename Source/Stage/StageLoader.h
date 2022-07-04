#pragma once
#include "Stage/StageInfo.h"
#include "Component/Graphics/InstancedRenderer.h"

#include "Component/Utility/BBModelHelper.h"
#include "Utility/InstancedRendererHelper.h"

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
	void loadStage(const StageInfo& stageInfo,
		std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers,
		GameObject** ppPlayer = nullptr, GameObject** ppPlayerModel = nullptr);

	GameObject* GetObj() { return childCollectItemObj;}

private:
	//ステージ土台作成
	void createStageBase(const StageInfo& stageInfo);

	//オブジェクト作成
	void createObjects(const StageInfo& stageInfo,
		std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers,
		GameObject** ppPlayer, GameObject** ppPlayerModel);

private:
	IGameMediator* m_pGameMediator;
	InstancingMaterial* m_pMaterial;
	GameObject* parentCollectItemObj;
	GameObject* childCollectItemObj;
};