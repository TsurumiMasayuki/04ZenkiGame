#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Audio/AudioSource.h"
#include "Device/GameDevice.h"
#include "Graphics/DX12/Material/DefaultMaterials.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Follow/Follow.h"
#include "Component/Follow/LerpFollow.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

#include "Stage/StageLoader.h"

#include "Utility/JsonFileManager.h"

#include "Component/Map/GoalObject.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Component/Item/CollectItemUI.h"
#include "Component/TestUI/TimeLimitUi.h"

std::string HogeScene::nextScene()
{
	return  pGoalObj->GetIsGoal() ? "Clear" : "GameOver";
}

bool HogeScene::isEnd()
{
	return m_pSceneEndEffect->IsEnd();
}

void HogeScene::start()
{
	TimeLimitUi::SetDead(false);

	if (!TimeLimitUi::IsDead())
	{
		{
			//頂点
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

			//法線
			DirectX::XMFLOAT3 normals[6] =
			{
				{  0.0f,  1.0f,  0.0f },
				{  0.0f,  0.0f, -1.0f },
				{  1.0f,  0.0f,  0.0f },
				{  0.0f,  0.0f,  1.0f },
				{ -1.0f,  0.0f,  0.0f },
				{  0.0f, -1.0f,  0.0f }
			};

			//インデックス
			int baseIndices[36] =
			{
				0, 4, 6, 6, 2, 0,	//上
				3, 2, 6, 6, 7, 3,	//後
				7, 6, 4, 4, 5, 7,	//右
				5, 1, 3, 3, 7, 5,	//前
				1, 0, 2, 2, 3, 1,	//左
				5, 4, 0, 0, 1, 5	//下
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

		//Blockbenchモデル読み込み
		{
			m_BBModelLoader.load("Resources/BBModels/player.geo.json", "Player", "Player");
			m_BBModelLoader.load("Resources/BBModels/moster_03.geo.json", "monster_03", "monster_03");
			m_BBModelLoader.load("Resources/BBModels/moster_04.geo.json", "monster_04", "monster_04");
			m_BBModelLoader.load("Resources/BBModels/moster_04b.geo.json", "monster_04b", "monster_04b");
			m_BBModelLoader.load("Resources/BBModels/block_wall.geo.json", "block_wall", "block_wall");
			m_BBModelLoader.load("Resources/BBModels/block_floor.json", "block_floor", "block_floor");
			m_BBModelLoader.load("Resources/BBModels/block_door.geo.json", "block_door_tex", "block_door_tex");
		}

		auto bbModel = m_BBModelLoader.getModel("Player");

		auto pRendererObj = new GameObject(this);
		{
			auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
			pRenderer->setMesh(m_pCube);
			m_RenderHelpers.emplace("Player", new InstancedRendererHelper<BBInstanceInfo>(bbModel, pRenderer));
		}
		{
			auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
			pRenderer->setMesh(m_pCube);
			m_RenderHelpers.emplace("monster_03", new InstancedRendererHelper<BBInstanceInfo>(m_BBModelLoader.getModel("monster_03"), pRenderer));
		}
		{
			auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
			pRenderer->setMesh(m_pCube);
			m_RenderHelpers.emplace("monster_04", new InstancedRendererHelper<BBInstanceInfo>(m_BBModelLoader.getModel("monster_04"), pRenderer));
		}
		{
			auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
			pRenderer->setMesh(m_pCube);
			m_RenderHelpers.emplace("monster_04b", new InstancedRendererHelper<BBInstanceInfo>(m_BBModelLoader.getModel("monster_04b"), pRenderer));
		}
		{
			auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
			pRenderer->setMesh(m_pCube);
			m_RenderHelpers.emplace("block_wall", new InstancedRendererHelper<BBInstanceInfo>(m_BBModelLoader.getModel("block_wall"), pRenderer));
		}
		{
			auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
			pRenderer->setMesh(m_pCube);
			m_RenderHelpers.emplace("block_floor", new InstancedRendererHelper<BBInstanceInfo>(m_BBModelLoader.getModel("block_floor"), pRenderer));
		}

		//ステージ生成
		JsonFileManager<StageInfo>::getInstance().load("Map1", "Resources/Map1.json");
		m_pStageLoader = new StageLoader(this);
		m_pStageLoader->loadStage(JsonFileManager<StageInfo>::getInstance().get("Map1"), m_RenderHelpers, &m_pPlayer, &m_pPlayerModel);
		pGoalObj = m_pStageLoader->GetGoal();

		//カメラ関係の設定
		auto& cameraTransform = getMainCamera()->getUser().getTransform();

		getMainCamera()->setTarget(m_pPlayer);

		auto* pCameraObject = &getMainCamera()->getUser();
		pCameraObject->addComponent<Action::ActionManager>();

		auto pFollow = pCameraObject->addComponent<LerpFollow>();
		pFollow->SetGameObject(m_pPlayer);
		pFollow->Setdistance(Vec3(5.0f, 0.0f, -10.0f));

		//Sound関連
		//Sound関連用Object生成
		GameObject* m_pSound = new GameObject(this);
		auto pAudio = m_pSound->addComponent<AudioSource>();
		//各種データ設定
		pAudio->setAudio("Stage1");
		pAudio->setVolume(0.1f);
		//再生
		pAudio->play(255);

		//SceneEffectオブジェクト生成
		pSceneEndEffect = new GameObject(this);
		m_pSceneEndEffect = pSceneEndEffect->addComponent<SceneEffect>();
		m_pSceneEndEffect->Initialize(1);
		pSceneStartEffect = new GameObject(this);
		m_pSceneStartEffect = pSceneStartEffect->addComponent<SceneEffect>();
		m_pSceneStartEffect->Initialize(0);
		m_pSceneStartEffect->StartEffect();
	}
}

void HogeScene::update()
{

	if (m_pSceneStartEffect->IsEnd())
	{
		std::vector<DirectX::XMMATRIX> matrices;
		matrices.emplace_back(DirectX::XMMatrixRotationY(MathUtility::toRadian(180.0f)) *
			DirectX::XMMatrixRotationZ(MathUtility::toRadian(-90.0f)) *
			m_pPlayerModel->getTransform().getWorldMatrix());
		m_RenderHelpers.at("Player")->appendInstanceInfo(matrices);

		for (auto renderHelper : m_RenderHelpers)
		{
			renderHelper.second->sendInstanceInfo();
		}

		
			if (!TimeLimitUi::IsDead())
			{
				std::vector<DirectX::XMMATRIX> matrices;
				matrices.emplace_back(DirectX::XMMatrixRotationY(MathUtility::toRadian(180.0f)) *
					DirectX::XMMatrixRotationZ(MathUtility::toRadian(-90.0f)) *
					m_pPlayerModel->getTransform().getWorldMatrix());
				m_RenderHelpers.at("Player")->appendInstanceInfo(matrices);
				m_RenderHelpers.at("Player")->sendInstanceInfo();
			}
			if (pGoalObj->GetIsGoal() || TimeLimitUi::IsDead())
			{
				m_pSceneEndEffect->StartEffect();
			}

		
	}
}

void HogeScene::shutdown()
{
	if (TimeLimitUi::IsDead())
	{
		delete m_pCube;
		delete m_pStageLoader;

		m_BBModelLoader.unLoadModels();

		for (auto& pair : m_RenderHelpers)
		{
			delete pair.second;
		}

		m_RenderHelpers.clear();
	}
}