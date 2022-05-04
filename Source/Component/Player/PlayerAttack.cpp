#include "PlayerAttack.h"
#include "Actor/Base/GameObject.h"
#include "Component/Graphics/Camera.h"

#include "Component/Physics/BoxColliderBt.h"

#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"

#include "Effect/TestFlameEffect.h"
#include "Effect/TestVibrationEffect.h"

void PlayerAttack::onStart()
{
	//自身にコライダーをアタッチ
	auto pBoxCollider = getUser().addComponent<BoxColiiderBt>();
	pBoxCollider->setMass(1.0f);
	pBoxCollider->setTrigger(true);
	pBoxCollider->setUseGravity(false);

	//自身にActionManagerをアタッチ
	auto pActionManager = getUser().addComponent<Action::ActionManager>();
	//火炎エフェクトを実行
	pActionManager->enqueueAction(new Action::TestFlameEffect());
	//自身を破棄
	pActionManager->enqueueAction(new Action::Destroy(3.0f));

	//カメラがアタッチされているオブジェクトを取得
	auto pCameraObject = &getUser().getGameMediator()->getMainCamera()->getUser();

	//ActionManagerを取得
	m_pCameraActionManager = pCameraObject->getComponent<Action::ActionManager>();
}

void PlayerAttack::onUpdate()
{
}

void PlayerAttack::onCollisionEnter(GameObject* pHit)
{
	//敵でないならreturn
	if (!pHit->compareTag("Enemy")) 
		return;

	if (m_pCameraActionManager->actionCount() > 0) 
		return;

	//カメラを揺らす
	m_pCameraActionManager->enqueueAction(new Action::EaseInBounce(new Action::RotateBy(Vec3(1.0f, 0.0f, 0.0f), 0.5f)));
	m_pCameraActionManager->enqueueAction(new Action::EaseInBounce(new Action::RotateBy(Vec3(-1.0f, 0.0f, 0.0f), 0.5f)));
}
