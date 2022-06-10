#include "StageLoader.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Graphics/DX12/Material/DefaultMaterials.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/PhalanxEnemy.h"
#include "Utility/CoordConverter.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

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

void StageLoader::loadStage(const StageInfo& stageInfo)
{
	createStageBase(stageInfo);
	createObjects(stageInfo);
}

void StageLoader::createStageBase(const StageInfo& stageInfo)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	//面の数
	const int faceCount = 36;
	//角度
	const float rad = DirectX::XM_2PI / faceCount;
	//円柱の半径
	const float radius = stageInfo.m_Radius - 1.0f;

	//円柱を生成
	for (int i = 0; i < faceCount; i++)
	{
		Vec3 cylinder(radius, rad * i, stageInfo.m_Length * 0.5f);

		//ゲームオブジェクト生成
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.7f, 0.7f, 0.7f, 1.0f));

		//座標設定
		pFloor->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(cylinder));
		//サイズ設定
		pFloor->getTransform().setLocalScale(Vec3(1.0f, radius * 0.25f, stageInfo.m_Length));
		//回転設定
		pFloor->getTransform().setLocalAngleZ(MathUtility::toDegree(rad * i));
	}
}

void StageLoader::createObjects(const StageInfo& stageInfo)
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pWallInstanceObject = ModelGameObjectHelper::instantiateModel<InstanceInfo>(m_pGameMediator, pCube, true);
	auto pWallInstancedRenderer = pWallInstanceObject->getChildren().at(0)->getComponent<InstancedRenderer<InstanceInfo>>();

	std::vector<InstanceInfo> instanceInfo;

	//オブジェクト配置情報を走査
	for (auto& objectPlaceInfo : stageInfo.m_ObjectPlaceInfoList)
	{
		//オブジェクト生成
		if (objectPlaceInfo.m_ObjectName == "Wall")
		{
			auto pObject = new GameObject(m_pGameMediator);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//スケール設定
			pObject->getTransform().setLocalScale(Vec3(3.0f, stageInfo.m_Radius * 0.3f, 1.0f));
			//角度設定
			pObject->getTransform().setLocalAngleZ(objectPlaceInfo.m_Angle);

			auto& info = instanceInfo.emplace_back();

			DirectX::XMStoreFloat4x4(&info.m_InstanceMatrix, DirectX::XMMatrixTranspose(pObject->getTransform().getWorldMatrix()));
			DirectX::XMStoreFloat4(&info.m_InstanceColor, DirectX::Colors::LawnGreen);

			//コライダー追加
			auto pCollider = pObject->addComponent<BoxColiiderBt>();
			pCollider->setUseGravity(false);
			pCollider->setMass(0.0f);
			pCollider->getRigidBody()->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

			//角度設定
			pObject->getTransform().setLocalAngleZ(objectPlaceInfo.m_Angle);
		}

		if (objectPlaceInfo.m_ObjectName == "TestEnemy")
		{
			auto pObject = ModelGameObjectHelper::instantiateModel<int>(m_pGameMediator, pCube);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//敵用コンポーネント追加
			auto pTestEnemy = pObject->addComponent<TestEnemy>();
			pTestEnemy->init(-10.0f, 0.0f, stageInfo.m_Radius);
		}

		if (objectPlaceInfo.m_ObjectName == "PhalanxEnemy")
		{
			auto pObject = new GameObject(m_pGameMediator);
			pObject->getTransform().setLocalPosition(objectPlaceInfo.m_Position);
			//敵用コンポーネント追加
			auto pPhalanxEnemy = pObject->addComponent<PhalanxEnemy>();
			pPhalanxEnemy->init(objectPlaceInfo.m_Position,
				6, 0, 11.0f, -1.0f);

			pPhalanxEnemy->setSwing(5.0f);
		}
	}

	m_pMaterial->setMainTexture(GameDevice::getTextureManager().getTexture("BoxFill"));
	pWallInstancedRenderer->setMaterial(m_pMaterial);
	pWallInstancedRenderer->setInstanceInfo(instanceInfo);
	pWallInstancedRenderer->setInstanceCount(instanceInfo.size());
}