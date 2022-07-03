#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Map/GoalObject.h"
#include "Utility/InstancedRendererHelper.h"
#include "Blockbench/BlockbenchLoader.h"
#include "Component/TestUI/SceneEffect.h"
class DX12Mesh;
class StageLoader;
class BBModelMaterial;

struct BBInstanceInfo
{
	DirectX::XMFLOAT4X4 instanceMat;
	DirectX::XMFLOAT4 instanceColor;
	//XY, XY�œ����
	DirectX::XMFLOAT3X4 instanceUVOrigins;
	//XY, XY�œ����
	DirectX::XMFLOAT3X4 instanceUVSizes;
};

class HogeScene
	: public AbstractScene
{
public:
	virtual std::string nextScene() override;
	virtual bool isEnd() override;
	virtual void start() override;
	virtual void update() override;
	virtual void shutdown() override;

	std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*> GetRenderHelpers() { return m_RenderHelpers;}

private:
	DX12Mesh* m_pCube;
	StageLoader* m_pStageLoader;
	
	GoalObject* pGoalObj;
	GameObject* m_pPlayer;
	GameObject* m_pPlayerModel;

	//Blockbench�ǂݍ���
	BlockbenchLoader m_BBModelLoader;
	//�C���X�^���V���O�⏕
	std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*> m_RenderHelpers;
	BlockbenchLoader star_blockModelLoader;
//シーン遷移
	//開始
	GameObject* pSceneStartEffect;
	SceneEffect* m_pSceneStartEffect;
	//シーン開始エフェクトが終わったかどうか
	bool sceneStartEffectIsEnd;
	//終了
	GameObject* pSceneEndEffect;
	SceneEffect* m_pSceneEndEffect;
	//シーン終了エフェクトが終わったかどうか
	bool sceneEffectIsEnd;
	
};