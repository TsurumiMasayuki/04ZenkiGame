#pragma once
#include "Stage/StageInfo.h"
#include "Component/Graphics/InstancedRenderer.h"

#include "Component/Utility/BBModelHelper.h"
#include "Utility/InstancedRendererHelper.h"

#include "Component/Map/GoalObject.h"

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
	void loadStage(const StageInfo& stageInfo,
		std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers,
		GameObject** ppPlayer = nullptr, GameObject** ppPlayerModel = nullptr);

	GameObject* GetObj() { return childCollectItemObj;}

	//�S�[���I�u�W�F�N�g��Ԃ�
	GoalObject* GetGoal() { return m_pGoal;}
private:
	//�X�e�[�W�y��쐬
	void createStageBase(const StageInfo& stageInfo);

	//�I�u�W�F�N�g�쐬
	void createObjects(const StageInfo& stageInfo,
		std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers,
		GameObject** ppPlayer, GameObject** ppPlayerModel);

private:
	IGameMediator* m_pGameMediator;
	InstancingMaterial* m_pMaterial;
	GameObject* parentCollectItemObj;
	GameObject* childCollectItemObj;
	//�V�[���ɃS�[���I�u�W�F�N�g�̃f�[�^��n�����߂̎���
	GoalObject* m_pGoal;
};