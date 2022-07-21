#include "StageLoader.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Graphics/DX12/Material/DefaultMaterials.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/PhalanxEnemy.h"
#include "Component/Enemy/JumpingEnemy.h"
#include "Component/Enemy/PressEnemy.h"
#include "Component/Enemy/ZigzagEnemy.h"

#include "Obstacle/SlidingThrough.h"
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

#include "Component/Gimmick/BoundGimmick.h"

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

void StageLoader::loadStage(const StageInfo& stageInfo,
	std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers,
	GameObject** ppPlayer,
	GameObject** ppPlayerModel)
{
	createStageBase(stageInfo, renderHelpers);
	createObjects(stageInfo, renderHelpers, ppPlayer, ppPlayerModel);
}

void StageLoader::createStageBase(const StageInfo& stageInfo, std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	//é¢ã®æ•°
	const int faceCount = 18;
	//è§’åº¦
	const float rad = DirectX::XM_2PI / faceCount;
	//å††æŸ±ã®åŠå¾„
	const float radius = stageInfo.m_Radius;

	float floorSize = 4.2f;
	int zCount = (int)(stageInfo.m_Length / floorSize);

	//å††æŸ±ã‚’ç”Ÿæˆ
	for (int i = 0; i < faceCount; i++)
	{
		for (int j = 0; j < zCount; j++)
		{
			Vec3 cylinder(radius, rad * i, j * floorSize + floorSize * 0.5f);

			//ã‚²ãƒ¼ãƒ ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç”Ÿæˆ
			GameObject* pFloor = new GameObject(m_pGameMediator);

			//åº§æ¨™è¨­å®š
			pFloor->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(cylinder));
			//ã‚µã‚¤ã‚ºè¨­å®š
			pFloor->getTransform().setLocalScale(Vec3(0.5f, floorSize, floorSize));
			//å›žè»¢è¨­å®š
			pFloor->getTransform().setLocalAngleZ(MathUtility::toDegree(rad * i) - 10.0f);

			auto pModelObject = new GameObject(m_pGameMediator);
			pFloor->addChild(*pModelObject);

			pModelObject->getTransform().setLocalPosition(Vec3(0.0f, -0.5f, 0.0f));
			pModelObject->getTransform().setLocalScale(Vec3(1.0f / 16.0f));
			pModelObject->getTransform().setLocalAngles(Vec3(0.0f, 180.0f, -90.0f - 180.0f));
			pModelObject->addComponent<BBModelHelper>()->setRenderer(renderHelpers.at("block_floor"));
		}
	}
}

void StageLoader::createObjects(const StageInfo& stageInfo,
	std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*>& renderHelpers,
	GameObject** ppPlayer, GameObject** ppPlayerModel)
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
			*ppPlayer = new GameObject(m_pGameMediator);

			pPlayer = *ppPlayer;

			Vec3 fix = CoordConverter::cartesianToCylinder(objectPlaceInfo.m_Position);
			fix.x += 2.0f;

			*ppPlayerModel = new GameObject(m_pGameMediator);
			(*ppPlayer)->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(fix));
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
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);

			auto& info = instanceInfo.emplace_back();

			auto pModelObject = new GameObject(m_pGameMediator);
			pObject->addChild(*pModelObject);

			pModelObject->getTransform().setLocalScale(Vec3(1.0f / 16.0f));
			pModelObject->addComponent<BBModelHelper>()->setRenderer(renderHelpers.at("block_wall"));

			//ã‚³ãƒ©ã‚¤ãƒ€ãƒ¼è¿½åŠ 
			auto pCollider = pObject->addComponent<BoxColiiderBt>();
			pCollider->setUseGravity(false);
			pCollider->setMass(0.0f);
			pCollider->getRigidBody()->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		}

		if (objectPlaceInfo.m_ObjectName == "PhalanxEnemy")
		{
			auto pObject = new GameObject(m_pGameMediator);
			//æ•µç”¨ã‚³ãƒ³ãƒãƒ¼ãƒãƒ³ãƒˆè¿½åŠ 
			auto pPhalanxEnemy = pObject->addComponent<PhalanxEnemy>();
			pPhalanxEnemy->init(objectPlaceInfo.m_Position,
				6, 0, stageInfo.m_Radius, -1.0f);
			pPhalanxEnemy->setTarget(pPlayer);

			pPhalanxEnemy->setSwing(5.0f);

			for (int i = 0; i < pObject->getChildren().size(); i++)
			{
				auto pPhalanxObject = pObject->getChildren().at(i);
				auto pModelObject = new GameObject(m_pGameMediator);

				pModelObject->getTransform().setLocalScale(Vec3(0.1f));
				pModelObject->getTransform().setLocalAngles(Vec3(0.0f, 180.0f, -90.0f));

				pPhalanxObject->addChild(*pModelObject);

				if (i == 0)
					pModelObject->addComponent<BBModelHelper>()->setRenderer(renderHelpers.at("monster_04"));
				else
					pModelObject->addComponent<BBModelHelper>()->setRenderer(renderHelpers.at("monster_04b"));
			}
		}

		if (objectPlaceInfo.m_ObjectName == "ZiguZaguEnemy")
		{
			auto pObject = new GameObject(m_pGameMediator);
		}

		if (objectPlaceInfo.m_ObjectName == "PassingBlock")
		{
			auto pObject = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//ã‚¹ã‚±ãƒ¼ãƒ«è¨­å®š
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			//è§’åº¦è¨­å®š
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);
			//FÝ’è
			pObject->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Red, 1.0f));
			//“G—pƒRƒ“ƒ|[ƒlƒ“ƒg’Ç‰Á
			auto pSlidingThrough = pObject->addComponent<SlidingThrough>();
		}

		if (objectPlaceInfo.m_ObjectName == "Bound")
		{
			auto pObject = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//ã‚¹ã‚±ãƒ¼ãƒ«è¨­å®š
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			//è§’åº¦è¨­å®š
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);
			//FÝ’è
			pObject->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Yellow, 1.0f));
			//“G—pƒRƒ“ƒ|[ƒlƒ“ƒg’Ç‰Á
			auto pBound = pObject->addComponent<BoundGimmick>();
			pBound->setTarget(pPlayer);
		}

		if (objectPlaceInfo.m_ObjectName == "JumpEnemy")
		{
			auto pObject = new GameObject(m_pGameMediator);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//ã‚¹ã‚±ãƒ¼ãƒ«è¨­å®š
			pObject->getTransform().setLocalScale(objectPlaceInfo.m_Scale);
			//è§’åº¦è¨­å®š
			pObject->getTransform().setLocalAngles(objectPlaceInfo.m_Angles);

			auto pModelObject = new GameObject(m_pGameMediator);
			pModelObject->getTransform().setLocalScale(Vec3(0.1f));
			pModelObject->getTransform().setLocalAngles(Vec3(0.0f, 180.0f, 0.0f));
			pModelObject->addComponent<BBModelHelper>()->setRenderer(renderHelpers.at("monster_03"));

			pObject->addChild(*pModelObject);

			//“G—pƒRƒ“ƒ|[ƒlƒ“ƒg’Ç‰Á
			auto pJumpingEnemy = pObject->addComponent<JumpingEnemy>();
			pJumpingEnemy->setTarget(pPlayer);
			pJumpingEnemy->init(pObject->getTransform().getLocalPosition(),
				0.0f, 0.0f, 12.0f);
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

	m_pGoal = pGoal->addComponent<GoalObject>();
	m_pGoal->Initialize(pGoal->getTransform().getLocalPosition(), pPlayer);
	m_pMaterial->setMainTexture(GameDevice::getTextureManager().getTexture("BoxFill"));
	pWallInstancedRenderer->setMaterial(m_pMaterial);
	pWallInstancedRenderer->setInstanceInfo(instanceInfo);
	pWallInstancedRenderer->setInstanceCount(instanceInfo.size());
}