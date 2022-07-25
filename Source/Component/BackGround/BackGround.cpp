#include "BackGround.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/D2DTextRenderer.h"
#include "Utility/ModelGameObjectHelper.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Utility/Action/Actions.h"
#include "Graphics/DX12/Material/DefaultMaterials.h"
#include "Scene/Base/AbstractScene.h"
#include "Component/Follow/Follow.h"

void BackGround::onStart()
{
	GameObject* pCameraObject = &getUser().getGameMediator()->getMainCamera()->getUser();
	for (int i = 0; i < 6; i++)
	{
		backGrondObj[i] = new GameObject(getUser().getGameMediator());
		backGrondObj[i]->getTransform().setLocalScale(Vec3(1000, 1000, 1));

		backGrondObj[i]->addComponent<Follow>()->SetGameObject(pCameraObject);
		backGroundSprite[i] = backGrondObj[i]->addComponent<SpriteRenderer>();
		backGroundSprite[i]->setColor(Color(1, 1, 1, 1));
		backGroundSprite[i]->setTextureByName("backGround");
	}

	backGrondObj[1]->getTransform().setLocalPosition(Vec3(0, 0, -250));
	backGrondObj[2]->getTransform().setLocalPosition(Vec3(250, 0, 0));
	backGrondObj[3]->getTransform().setLocalPosition(Vec3(-250, 0, 0));
	backGrondObj[4]->getTransform().setLocalPosition(Vec3(0, 250, 0));
	backGrondObj[5]->getTransform().setLocalPosition(Vec3(0, -250, 0));

	backGrondObj[2]->getTransform().setLocalAngles(Vec3(0, 60, 0));
	backGrondObj[3]->getTransform().setLocalAngles(Vec3(0, -60, 0));
	backGrondObj[4]->getTransform().setLocalAngles(Vec3(60, 0, 0));
	backGrondObj[5]->getTransform().setLocalAngles(Vec3(-60, 0, 0));

	backGrondObj[0]->getComponent<Follow>()->Setdistance(Vec3(0, 0, 250));

	material = new InstancingMaterial();
	material->init(DX12GraphicsCore::g_pDevice.Get());

	auto& random = GameDevice::getRandom();
	//パーティクル(インスタンシング)
	instancedObj = ModelGameObjectHelper::instantiateModel<InstancingInfo>(m_pUser->getGameMediator(), GameDevice::getModelManager().getModel("Cube"), true);
	instancedObj->addComponent<Follow>()->SetGameObject(pCameraObject);
	instancedObj->getComponent<Follow>()->Setdistance(Vec3(0, 0, 250));
	instancedRenderer = instancedObj->getChildren().at(0)->getComponent<InstancedRenderer<InstancingInfo>>();
    
	for (int i = 0; i < 10; i++)
	{
		auto pos = Vec3(random.getRandom(-200, 200), random.getRandom(0, 15), random.getRandom(100, 700));
		backGroundParticle[i] = new GameObject(m_pUser->getGameMediator());
		backGroundParticle[i]->getTransform().setLocalPosition(Vec3(pos));
		backGroundParticle[i]->getTransform().setLocalScale(Vec3(5, 0.1f, 5));

		backGroundParticle[i]->addComponent<Action::ActionManager>()->enqueueAction
		(
			new Action::RepeatForever(
				new Action::Sequence
				(
					{
						new Action::EaseOutCubic(new Action::MoveTo(Vec3(pos.x,pos.y,pos.z - 500), 1.0f)),
						new Action::EaseOutCubic(new Action::MoveTo(Vec3(random.getRandom(-200, 200), random.getRandom(0, 15), random.getRandom(100,700)),0.0f))
					}
				)
		));
	}
}

void BackGround::onUpdate()
{
	for (int i = 0; i < 10; i++)
    {
	    auto& info = inctanceInfo.emplace_back();
	    DirectX::XMStoreFloat4x4(&info.instancingMatrix, DirectX::XMMatrixTranspose(backGroundParticle[i]->getTransform().getWorldMatrix()));
	    DirectX::XMStoreFloat4(&info.instancingColor, DirectX::Colors::OrangeRed);
	    
	    material->setMainTexture(GameDevice::getTextureManager().getTexture("BoxFill"));
	    instancedRenderer->setMaterial(material);
	    instancedRenderer->setInstanceInfo(inctanceInfo);
	    instancedRenderer->setInstanceCount(inctanceInfo.size());
	}

	inctanceInfo.clear();
}