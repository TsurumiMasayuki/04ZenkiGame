#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Enemy/TestEnemy.h"

#include "Component/Follow/Follow.h"
#include "Component/Map/Map.h"
#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Player/PlayerParamManager.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"
#include "Component/TestUI/TestUI.h"

#include "Utility/CoordConverter.h"

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
	auto pPlayerActionManager = pPlayer->addComponent<Action::ActionManager>();

	auto pModel = pPlayer->getChildren().at(0);
	pModel->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	pPlayer->getTransform().setLocalPosition(Vec3(0.0f, 0.0f, 0.0f));
	auto pPlayerParam = pPlayer->addComponent<PlayerParamManager>();
	auto pPlayerMove = pPlayer->addComponent<PlayerMovement>();

	//�U���p�I�u�W�F�N�g����
	auto pPlayerAttackObject = new GameObject(this);
	auto pPlayerAttack = pPlayerAttackObject->addComponent<PlayerAttack>();
	pPlayerAttack->init(&pModel->getTransform());

	pPlayerMove->init(pPlayerParam);
	pPlayerMove->setCylinderRadius(11.0f);

	//�J�����֌W�̐ݒ�
	auto& cameraTransform = getMainCamera()->getUser().getTransform();
	cameraTransform.setLocalPosition(Vec3(0.0f, 0.0f, 0.0f));
	cameraTransform.setLocalAngles(Vec3(30.0f, 0.0f, 0.0f));

	auto* pCameraObject = &getMainCamera()->getUser();
	pCameraObject->addComponent<Action::ActionManager>();

	auto pFollow = pCameraObject->addComponent<Follow>();
	pFollow->SetGameObject(pPlayer);
	pFollow->Setdistance(Vec3(0.0f, 8.0f, -8.0f));

	//�ʂ̐�
	const int faceCount = 24;
	//�p�x
	const float rad = DirectX::XM_2PI / faceCount;
	//�~���̔��a
	const float radius = 10.0f;

	//�~���𐶐�
	for (int i = 0; i < faceCount; i++)
	{
		Vec3 cylinder(radius, rad * i, 100.0f);

		//�Q�[���I�u�W�F�N�g����
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.7f, 0.7f, 0.7f, 1.0f));

		//���W�ݒ�
		pFloor->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(cylinder));
		//�T�C�Y�ݒ�
		pFloor->getTransform().setLocalScale(Vec3(1.0f, radius * 0.25f, 200.0f));
		//��]�ݒ�
		pFloor->getTransform().setLocalAngleZ(MathUtility::toDegree(rad * i));
	}

	//�e�X�g�p�G����
	auto pTestEnemyObject = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	pTestEnemyObject->getTransform().setLocalPosition(Vec3(11.0f, 0.0f, 50.0f));
	pTestEnemyObject->getTransform().setLocalScale(Vec3(1.0f, 1.0f, 1.0f));

	//�R���C�_�[�ǉ�
	auto pEnemyCollider = pTestEnemyObject->addComponent<BoxColiiderBt>();
	pEnemyCollider->setMass(1.0f);
	pEnemyCollider->setTrigger(false);
	pEnemyCollider->setUseGravity(false);
	pEnemyCollider->applyForceImpluse(Vec3(0.0f, 0.0f, -20.0f));

	auto pTestEnemy = pTestEnemyObject->addComponent<TestEnemy>();
	pTestEnemy->init(-10.0f, 0.0f);
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}