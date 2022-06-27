#include "CollectItemDraw.h"
#include <Math/MathUtility.h>
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Graphics/MeshRenderer.h"

void CollectItemDraw::onStart()
{
	{
		DX12Mesh::MeshVertex baseVertices[8] =
		{
			{ { 0.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { 0.0f, 0.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { 0.0f, 1.0f, 0.0f }, { -1.0f,  0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { 0.0f, 0.0f, 0.0f }, { -1.0f,  0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { 1.0f, 0.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { 1.0f, 1.0f, 0.0f }, {  1.0f,  0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { 1.0f, 0.0f, 0.0f }, {  0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } }
		};

		DirectX::XMFLOAT3 normals[6] =
		{
			{  0.0f,  1.0f,  0.0f },
			{  0.0f,  0.0f, -1.0f },
			{  1.0f,  0.0f,  0.0f },
			{  0.0f,  0.0f,  1.0f },
			{ -1.0f,  0.0f,  0.0f },
			{  0.0f, -1.0f,  0.0f }
		};

		int baseIndices[36] =
		{
			0, 4, 6, 6, 2, 0,	
			3, 2, 6, 6, 7, 3,	
			7, 6, 4, 4, 5, 7,	
			5, 1, 3, 3, 7, 5,	
			1, 0, 2, 2, 3, 1,	
			5, 4, 0, 0, 1, 5	
		};

		std::vector<DX12Mesh::MeshVertex> vertices;
		std::vector<USHORT> indices;
		vertices.resize(36);
		indices.resize(36);
		for (int i = 0; i < 36; i++)
		{
			vertices[i] = baseVertices[baseIndices[i]];
			vertices[i].normal = normals[baseIndices[i] % 6];
			indices[i] = i;
		}

		m_pCube = new DX12Mesh();
		m_pCube->init(DX12GraphicsCore::g_pDevice.Get(), vertices, indices, "BoxFill");
	}

	//モデル読み込み
	star_blockModelLoader.load("Resources/ui_crystal/crystal_red.geo.json", "ui_crystal", "ui_crystal");
	auto starModel = star_blockModelLoader.getModel("ui_crystal");
	auto starRenderer = getUser().addComponent<InstancedRenderer<BBInstanceInfo>>();
	starRenderer->setMesh(m_pCube);
	m_RenderHelpers.emplace("ui_crystal", new InstancedRendererHelper<BBInstanceInfo>(starModel, starRenderer));
	//UIオブジェクト生成
	GameObj = new GameObject(getUser().getGameMediator());
	CollectItemUIObj = GameObj->addComponent<CollectItemUI>();
}

void CollectItemDraw::onUpdate()
{
	if (!CollectItemUIObj->IsDead())
	{
		//モデル描画
	    std::vector<DirectX::XMMATRIX> matricesStar;
	    matricesStar.emplace_back(DirectX::XMMatrixRotationY(MathUtility::toRadian(1.0f)) *
	    	DirectX::XMMatrixRotationZ(MathUtility::toRadian(1.0f)) *
	    	getUser().getTransform().getWorldMatrix());
	    m_RenderHelpers.at("ui_crystal")->appendInstanceInfo(matricesStar);
	    m_RenderHelpers.at("ui_crystal")->sendInstanceInfo();
	}
}