#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Follow/Follow.h"
#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Player/PlayerParamManager.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

#include "Stage/StageLoader.h"

#include "Utility/JsonFileManager.h"

#include "Component/Map/GoalObject.h"

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
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	pPlayer->getTransform().setLocalScale(Vec3(1.0f));
	auto pPlayerActionManager = pPlayer->addComponent<Action::ActionManager>();

	auto pModel = pPlayer->getChildren().at(0);
	pModel->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	pPlayer->getTransform().setLocalPosition(Vec3(0.0f, 11.0f, 0.0f));
	auto pPlayerParam = pPlayer->addComponent<PlayerParamManager>();
	auto pPlayerMove = pPlayer->addComponent<PlayerMovement>();

	//攻撃用オブジェクト生成
	auto pPlayerAttackObject = new GameObject(this);
	auto pPlayerAttack = pPlayerAttackObject->addComponent<PlayerAttack>();
	pPlayerAttack->init(&pModel->getTransform(), pPlayerParam);

	pPlayerMove->init(pPlayerParam);
	pPlayerMove->setCylinderRadius(11.0f);

	//コライダー追加
	auto pCollider = pPlayer->addComponent<BoxColiiderBt>();
	pCollider->setMass(1.0f);
	pCollider->setTrigger(false);
	pCollider->setUseGravity(false);

	//カメラ関係の設定
	auto pCameraObject = &getMainCamera()->getUser();
	pCameraObject->addComponent<Action::ActionManager>();
	auto pFollow = pCameraObject->addComponent<Follow>();
	pFollow->Setdistance(Vec3(10.0f, 0.0f, -10.0f));
	pFollow->SetGameObject(pPlayer);

	auto& cameraTransform = getMainCamera()->getUser().getTransform();
	getMainCamera()->setTarget(pPlayer);

	//ステージ読み込み
	JsonFileManager<StageInfo>::getInstance().load("PrototypeStage", "Resources/PrototypeStage.json");
	StageLoader stageLoader(this);
	stageLoader.loadStage(JsonFileManager<StageInfo>::getInstance().get("PrototypeStage"));

	//ゴールを設定
	//ゴールオブジェクト生成
	auto pGoalObject = new GameObject(this);
	//UI生成
	goalObject = pGoalObject->addComponent<GoalObject>();
	goalObject->Initialize(100, pPlayer);
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}