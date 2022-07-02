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
#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Player/PlayerParamManager.h"
#include "Component/Player/PlayerSound.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

#include "Stage/StageLoader.h"

#include "Utility/JsonFileManager.h"

#include "Component/Map/GoalObject.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Component/Item/CollectItemUI.h"

std::string HogeScene::nextScene()
{
	return std::string();
}

bool HogeScene::isEnd()
{
	return false;
}

void HogeScene::start()
{
	//ステージ生成
	JsonFileManager<StageInfo>::getInstance().load("PrototypeStage", "Resources/PrototypeStage.json");
	m_pStageLoader = new StageLoader(this);
	m_pStageLoader->loadStage(JsonFileManager<StageInfo>::getInstance().get("PrototypeStage"));

	auto pCube = GameDevice::getModelManager().getModel("Cube");

	m_pPlayer = new GameObject(this);
	m_pPlayerModel = new GameObject(this);
	m_pPlayerModel->getTransform().setLocalScale(Vec3(0.1f));
	m_pPlayer->addChild(*m_pPlayerModel);
	auto pPlayerActionManager = m_pPlayer->addComponent<Action::ActionManager>();

	auto pPlayerParam = m_pPlayer->addComponent<PlayerParamManager>();
	auto pPlayerMove = m_pPlayer->addComponent<PlayerMovement>();
	auto pPlayerSound = m_pPlayer->addComponent<PlayerSound>();

	//攻撃用オブジェクト生成
	auto pPlayerAttackObject = new GameObject(this);
	auto pPlayerAttack = pPlayerAttackObject->addComponent<PlayerAttack>();
	pPlayerAttack->init(&m_pPlayerModel->getTransform(), pPlayerParam);

	pPlayerMove->init(pPlayerParam);
	pPlayerMove->setCylinderRadius(11.0f);

	//コライダー追加
	auto pCollider = m_pPlayer->addComponent<BoxColiiderBt>();
	pCollider->setUseGravity(false);
	pCollider->setTrigger(false);
	pCollider->setMass(1.0f);
	pCollider->getRigidBody()->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);

	//カメラ関係の設定
	auto& cameraTransform = getMainCamera()->getUser().getTransform();

	getMainCamera()->setTarget(m_pPlayer);

	auto* pCameraObject = &getMainCamera()->getUser();
	pCameraObject->addComponent<Action::ActionManager>();

	auto pFollow = pCameraObject->addComponent<LerpFollow>();
	pFollow->SetGameObject(m_pPlayer);
	pFollow->Setdistance(Vec3(8.0f, 0.0f, -8.0f));

	//ゴールを設定
	//ゴールオブジェクト生成
	auto pGoalObject = new GameObject(this);
	//UI生成
	//goalObject = pGoalObject->addComponent<GoalObject>();
	//goalObject->Initialize(JsonFileManager<StageInfo>::getInstance().get("PrototypeStage").m_Length, m_pPlayer);

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
	}

	auto bbModel = m_BBModelLoader.getModel("Player");

	auto pRendererObj = new GameObject(this);
	auto pRenderer = pRendererObj->addComponent<InstancedRenderer<BBInstanceInfo>>();
	pRenderer->setMesh(m_pCube);

	m_RenderHelpers.emplace("Player", new InstancedRendererHelper<BBInstanceInfo>(bbModel, pRenderer));

	//Sound関連
	//Sound関連用Object生成
	GameObject* m_pSound = new GameObject(this);
	auto pAudio = m_pSound->addComponent<AudioSource>();
	//各種データ設定
	pAudio->setAudio("Stage1");
	pAudio->setVolume(0.1f);
	//再生
	pAudio->play(255);

}

void HogeScene::update()
{
	std::vector<DirectX::XMMATRIX> matrices;
	matrices.emplace_back(DirectX::XMMatrixRotationY(MathUtility::toRadian(180.0f)) *
		DirectX::XMMatrixRotationZ(MathUtility::toRadian(-90.0f)) *
		m_pPlayerModel->getTransform().getWorldMatrix());
	m_RenderHelpers.at("Player")->appendInstanceInfo(matrices);
	m_RenderHelpers.at("Player")->sendInstanceInfo();
}

void HogeScene::shutdown()
{
	delete m_pCube;
	delete m_pStageLoader;

	m_BBModelLoader.unLoadModels();
	star_blockModelLoader.unLoadModels();

	for (auto& pair : m_RenderHelpers)
	{
		delete pair.second;
	}
}