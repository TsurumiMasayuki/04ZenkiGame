#include "HogeScene.h"
#include "Actor/Base/GameObject.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/LinearlyEnemy.h"

#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"

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
	auto& cameraTransform = getMainCamera()->getUser().getTransform();
	cameraTransform.setLocalPosition(Vec3(0.0f, 6.0f, 0.0f));
	cameraTransform.setLocalAngles(Vec3(10.0f, 0.0f, 0.0f));

	getMainCamera()->getUser().addComponent<Action::ActionManager>();

	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	auto pPlayerActionManager = pPlayer->addComponent<Action::ActionManager>();

	auto pModel = pPlayer->getChildren().at(0);
	pModel->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	pPlayer->getTransform().setLocalPosition(Vec3(0.0f, 0.0f, 3.0f));
	auto pPlayerParam = pPlayer->addComponent<PlayerParamManager>();
	auto pPlayerMove = pPlayer->addComponent<PlayerMovement>();

	auto pPlayerAttackObject = new GameObject(this);
	pPlayerAttackObject->getTransform().setLocalPosition(Vec3(0.0f, 0.0f, 1.0f));
	pPlayerAttackObject->setParent(pPlayer);
	auto pPlayerAttack = pPlayerAttackObject->addComponent<PlayerAttack>();
	pPlayerAttack->init(pPlayerActionManager);

	pPlayerMove->init(pPlayerParam);
	pPlayerMove->setCylinderRadius(5.0f);

	//�ʂ̐�
	const int faceCount = 12;
	//�p�x
	const float rad = DirectX::XM_PI / faceCount;
	//�~���𐶐�
	for (int i = 0; i < faceCount; i++)
	{
		Vec3 cylinder(4.0f, rad * i, 10.0f);

		//�Q�[���I�u�W�F�N�g����
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.7f, 0.7f, 0.7f, 1.0f));

		//���W�ݒ�
		pFloor->getTransform().setLocalPosition(CoordConverter::cylinderToCartesian(cylinder));
		//�T�C�Y�ݒ�
		pFloor->getTransform().setLocalScale(Vec3(1.0f, 1.0f, 20.0f));
		//��]�ݒ�
		pFloor->getTransform().setLocalAngleZ(MathUtility::toDegree(rad * i));
	}
}

void HogeScene::update()
{
}

void HogeScene::shutdown()
{
}