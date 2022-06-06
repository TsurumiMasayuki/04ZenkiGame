#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Follow/Follow.h"
#include "Component/Follow/LerpFollow.h"
#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Player/PlayerParamManager.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

#include "Stage/StageLoader.h"

#include "Utility/JsonFileManager.h"

#include "Component/Map/GoalObject.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

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
	//�X�e�[�W�ǂݍ���
	JsonFileManager<StageInfo>::getInstance().load("PrototypeStage", "Resources/PrototypeStage.json");
	StageLoader stageLoader(this);
	stageLoader.loadStage(JsonFileManager<StageInfo>::getInstance().get("PrototypeStage"));

	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	auto pPlayerActionManager = pPlayer->addComponent<Action::ActionManager>();

	auto pModel = pPlayer->getChildren().at(0);
	pModel->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	auto pPlayerParam = pPlayer->addComponent<PlayerParamManager>();
	auto pPlayerMove = pPlayer->addComponent<PlayerMovement>();

	//�U���p�I�u�W�F�N�g����
	auto pPlayerAttackObject = new GameObject(this);
	auto pPlayerAttack = pPlayerAttackObject->addComponent<PlayerAttack>();
	pPlayerAttack->init(&pModel->getTransform(), pPlayerParam);

	pPlayerMove->init(pPlayerParam);
	pPlayerMove->setCylinderRadius(11.0f);

	//�R���C�_�[�ǉ�
	auto pCollider = pPlayer->addComponent<BoxColiiderBt>();
	pCollider->setUseGravity(false);
	pCollider->setTrigger(false);
	pCollider->setMass(1.0f);
	pCollider->getRigidBody()->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);

	//�J�����֌W�̐ݒ�
	auto& cameraTransform = getMainCamera()->getUser().getTransform();

	getMainCamera()->setTarget(pPlayer);

	auto* pCameraObject = &getMainCamera()->getUser();
	pCameraObject->addComponent<Action::ActionManager>();

	auto pFollow = pCameraObject->addComponent<LerpFollow>();
	pFollow->SetGameObject(pPlayer);
	pFollow->Setdistance(Vec3(8.0f, 0.0f, -8.0f));

	//�S�[����ݒ�
	//�S�[���I�u�W�F�N�g����
	auto pGoalObject = new GameObject(this);
	//UI����
	goalObject = pGoalObject->addComponent<GoalObject>();
	goalObject->Initialize(JsonFileManager<StageInfo>::getInstance().get("PrototypeStage").m_Length, pPlayer);
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}