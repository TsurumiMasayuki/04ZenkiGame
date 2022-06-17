#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Map/GoalObject.h"
#include "Utility/InstancedRendererHelper.h"
#include "Blockbench/BlockbenchLoader.h"

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

private:
	DX12Mesh* m_pCube;
	StageLoader* m_pStageLoader;
	GoalObject* goalObject= nullptr;

	GameObject* m_pPlayer;
	GameObject* m_pPlayerModel;

	//Blockbench�ǂݍ���
	BlockbenchLoader m_BBModelLoader;
	//�C���X�^���V���O�⏕
	std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*> m_RenderHelpers;
};