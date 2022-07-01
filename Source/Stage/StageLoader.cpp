#include "StageLoader.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Graphics/DX12/Material/DefaultMaterials.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/PhalanxEnemy.h"
#include "Obstacle/SlidingThrough.h"
#include "Component/Enemy/JumpingEnemy.h"
#include "Component/Item/CollectItem.h"
#include "Component/Item/CollectItemDraw.h"
#include "Utility/CoordConverter.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Player/PlayerParamManager.h"
#include "Component/Player/PlayerSound.h"
#include "Component/Player/PlayerDamage.h"

#include "Component/Map/GoalObject.h"

#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"

StageLoader::StageLoader(IGameMediator* pGameMediator)
	: m_pGameMediator(pGameMediator),
	m_pMaterial(new InstancingMaterial())
{
	m_pMaterial->init(DX12GraphicsCore::g_pDevice.Get());
}

StageLoader::~StageLoader()
{
	delete m_pMaterial;
}

void StageLoader::loadStage(const StageInfo& stageInfo, GameObject** ppPlayer, GameObject** ppPlayerModel)
{
	createStageBase(stageInfo);
	createObjects(stageInfo, ppPlayer, ppPlayerModel);
}

void StageLoader::createStageBase(const StageInfo& stageInfo)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	//é¢ã®æ•°
	const int faceCount = 36;
	//è§’åº¦
	const float rad = DirectX::XM_2PI / faceCount;
	//å††æŸ±ã®åŠå¾„
	const float radius = stageInfo.m_Radius;

	//å††æŸ±ã‚’ç”Ÿæˆ
	for (int i = 0; i < faceCount; i++)
	{
		Vec3 cylinder(radius, rad * i, stageInfo.m_Length * 0.5f);

		//ã‚²ãƒ¼ãƒ ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç”Ÿæˆ
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.7f, 0.7f, 0.7f, 1.0f));

		//åº§æ¨™è¨­å®š
		pFloor->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(cylinder));
		//ã‚µã‚¤ã‚ºè¨­å®š
		pFloor->getTransform().setLocalScale(Vec3(1.0f, radius * 0.25f, stageInfo.m_Length));
		//å›žè»¢è¨­å®š
		pFloor->getTransform().setLocalAngleZ(MathUtility::toDegree(rad * i));
	}
}

void StageLoader::createObjects(const StageInfo& stageInfo, GameObject** ppPlayer, GameObject** ppPlayerModel)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pWallInstanceObject = ModelGameObjectHelper::instantiateModel<InstanceInfo>(m_pGameMediator, pCube, true);
	auto pWallInstancedRenderer = pWallInstanceObject->getChildren().at(0)->getComponent<InstancedRenderer<InstanceInfo>>();

	std::vector<InstanceInfo> instanceInfo;

	GameObject* pPlayer = nullptr;
	GameObject* pGoal = nullptr;

	//オブジェクト配置情報を走査
	for (auto& objectPlaceInfo : stageInfo.m_ObjectPlaceInfoList)
	{
		if (objectPlaceInfo.m_ObjectName == "Player")
		{
			auto pCube = GameDevice::getModelManager().getModel("Cube");

			*ppPlayer = new GameObject(m_pGameMediator);

			pPlayer = *ppPlayer;

			*ppPlayerModel = new GameObject(m_pGameMediator);
			(*ppPlayer)->getTransform().setLocalScale(Vec3(0.1f));
			(*ppPlayer)->addChild((**ppPlayerModel));
			auto pPlayerActionManager = (*ppPlayer)->addComponent<Action::ActionManager>();

			auto pPlayerParam = (*ppPlayer)->addComponent<PlayerParamManager>();
			auto pPlayerMove = (*ppPlayer)->addComponent<PlayerMovement>();
			auto pPlayerSound = (*ppPlayer)->addComponent<PlayerSound>();

			//攻撃用
			auto pPlayerAttack = pPlayer->addComponent<PlayerAttack>();
			pPlayerAttack->init(&(*ppPlayerModel)->getTransform(), pPlayerParam);

			pPlayerMove->init(pPlayerParam);
			pPlayerMove->setCylinderRadius(12.0f);

			//ダメージを受ける用
			pPlayer->addComponent<PlayerDamage>()->init(pPlayerAttack, pPlayerParam);

			//コライダー追加
			auto pCollider = (*ppPlayer)->addComponent<BoxColiiderBt>();
			pCollider->setUseGravity(false);
			pCollider->setTrigger(false);
			pCollider->setMass(1.0f);
			pCollider->getRigidBody()->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		}

		//オブジェクト生成
		if (objectPlaceInfo.m_ObjectName == "BaseWall" ||
			objectPlaceInfo.m_ObjectName == "GarssBlock")
		{
			auto pObject = new GameObject(m_pGameMediator);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//ã‚¹ã‚±ãƒ¼ãƒ«è¨­å®š
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			//è§’åº¦è¨­å®š
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);

			auto& info = instanceInfo.emplace_back();

			DirectX::XMStoreFloat4x4(&info.m_InstanceMatrix, DirectX::XMMatrixTranspose(pObject->getTransform().getWorldMatrix()));
			DirectX::XMStoreFloat4(&info.m_InstanceColor, DirectX::Colors::LawnGreen);

			//ã‚³ãƒ©ã‚¤ãƒ€ãƒ¼è¿½åŠ 
			auto pCollider = pObject->addComponent<BoxColiiderBt>();
			pCollider->setUseGravity(false);
			pCollider->setMass(0.0f);
			pCollider->getRigidBody()->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		}

		if (objectPlaceInfo.m_ObjectName == "Enemy")
		{
			auto pObject = new GameObject(m_pGameMediator);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//æ•µç”¨ã‚³ãƒ³ãƒãƒ¼ãƒãƒ³ãƒˆè¿½åŠ 
			auto pPhalanxEnemy = pObject->addComponent<PhalanxEnemy>();
			pPhalanxEnemy->init(objectPlaceInfo.m_Position,
				6, 0, 12.0f, -1.0f);

			pPhalanxEnemy->setSwing(5.0f);
		}

		if (objectPlaceInfo.m_ObjectName == "PassingBlock")
		{
			auto pObject = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//ã‚¹ã‚±ãƒ¼ãƒ«è¨­å®š
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			//è§’åº¦è¨­å®š
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);
			Vec3 modelPosition = objectPlaceInfo.m_Position.normalized() * 2.0f;
			float x = modelPosition.x;
			float y = modelPosition.y;
			modelPosition.x = y;
			modelPosition.y = x;
			modelPosition.z = 0.0f;
			pObject->getChildren().at(0)->getTransform().setLocalPosition(modelPosition);
			//FÝ’è
			pObject->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Red, 1.0f));
			//“G—pƒRƒ“ƒ|[ƒlƒ“ƒg’Ç‰Á
			auto pSlidingThrough = pObject->addComponent<SlidingThrough>();
		}

		if (objectPlaceInfo.m_ObjectName == "JumpingEnemy")
		{
			auto pObject = new GameObject(m_pGameMediator);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//ã‚¹ã‚±ãƒ¼ãƒ«è¨­å®š
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			//è§’åº¦è¨­å®š
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);
			//“G—pƒRƒ“ƒ|[ƒlƒ“ƒg’Ç‰Á
			auto pJumpingEnemy = pObject->addComponent<JumpingEnemy>();
			pJumpingEnemy->init(pObject->getTransform().getLocalPosition(),
				1.0f, 0, 12.0f);
		}

		if (objectPlaceInfo.m_ObjectName == "CollectItem")
		{
			parentCollectItemObj = new GameObject(m_pGameMediator);
			parentCollectItemObj->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			childCollectItemObj = new GameObject(m_pGameMediator);
			childCollectItemObj->getTransform().setLocalScale(Vec3(stageInfo.m_Radius, stageInfo.m_Radius, stageInfo.m_Radius));
			parentCollectItemObj->addChild(*childCollectItemObj);
			auto pCollectItem = parentCollectItemObj->addComponent<CollectItem>();
			auto pCollectItemDraw = childCollectItemObj->addComponent<CollectItemDraw>();
		}

		if (objectPlaceInfo.m_ObjectName == "Goal")
		{
			//ゴールを設定
			pGoal = new GameObject(m_pGameMediator);
			pGoal->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			pGoal->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);
		}
	}

	pGoal->addComponent<GoalObject>()->Initialize(pGoal->getTransform().getLocalPosition(), pPlayer);

	m_pMaterial->setMainTexture(GameDevice::getTextureManager().getTexture("BoxFill"));
	pWallInstancedRenderer->setMaterial(m_pMaterial);
	pWallInstancedRenderer->setInstanceInfo(instanceInfo);
	pWallInstancedRenderer->setInstanceCount(instanceInfo.size());
}