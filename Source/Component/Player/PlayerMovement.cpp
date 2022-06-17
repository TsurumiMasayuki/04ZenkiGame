#include "PlayerMovement.h"
#include "Actor/Base/GameObject.h"

#include "Component/Audio/AudioSource.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

#include "Physics/IPhysicsManager.h"

#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerParamManager.h"

#include "Device/GameInput.h"

#include "Effect/TestFlameEffect.h"

#include "Utility/JsonFileManager.h"
#include "Utility/CoordConverter.h"

#include "btBulletDynamicsCommon.h"

using namespace Action;

void PlayerMovement::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");

	m_CylinderCoord.y = MathUtility::toRadian(90.0f);
	m_CylinderCoord.z = getTransform().getLocalPosition().z;

	m_pActionManager = getUser().getComponent<Action::ActionManager>();

	m_pBoxCollider = getUser().getComponent<BoxColiiderBt>();

	Vec3 cartCoord = CoordConverter::cylinderToCartesian(m_CylinderCoord);
	getTransform().setLocalPosition(cartCoord);
}

void PlayerMovement::onUpdate()
{
	m_PrePosition = getTransform().getLocalPosition();
	m_CylinderCoord.z = m_PrePosition.z;

	//入力デバイスを取得
	const auto& input = GameDevice::getInput();

	//設定ファイルをホットリロード
	if (input.isKeyDown(DIK_R))
	{
		m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
	}

	//移動方向
	Vec3 moveDir = GameInput::getInstance().getPlayerMove();

	//ダッシュボタンが押されているなら&燃料がゼロでないなら
	if (GameInput::getInstance().getPlayerDash() &&
		!m_pPlayerParam->isFuelZero())
	{
		if (m_pActionManager->actionCount() == 0)
		{
			//間隔を開けて火炎エフェクト
			auto pSequence = new Action::Sequence(
				{
					new Action::TestFlameEffect(m_pActionManager),
					new Action::WaitForSeconds(0.1f)
				}
			);

			//リピート実行
			auto pRepeat = new Action::RepeatForever(pSequence);

			m_pActionManager->enqueueAction(pRepeat);
		}

		dash(moveDir);
	}
	else
	{
		//エフェクト停止
		if (m_pActionManager->actionCount() == 1)
			m_pActionManager->forceNext();

		move(moveDir);
	}

	convertCoord();
		
	//回転を決める
	float yAngle = moveDir.x == 0.0f ? 0.0f : moveDir.x * 50.0f - moveDir.z * 35.0f;

	Vec3 angles = getUser().getChildren().at(0)->getTransform().getLocalAngles();
	angles.x = yAngle;
	getUser().getChildren().at(0)->getTransform().setLocalAngles(angles);

	//回転
	getTransform().setLocalAngles(Vec3(0.0f, 0.0f, MathUtility::toDegree(m_CylinderCoord.y)));
}

void PlayerMovement::init(PlayerParamManager* pPlayerParam)
{
	m_pPlayerParam = pPlayerParam;
}

void PlayerMovement::setCylinderRadius(float radius)
{
	m_CylinderCoord.x = radius;
}

void PlayerMovement::move(const Vec3& moveDir)
{
	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//移動量を算出
	float move = m_Stats.m_WalkSpeed * deltaTime;

	//座標更新
	m_CylinderCoord.y -= moveDir.x * deltaTime;
	m_CylinderCoord.z += moveDir.z * move;
}

void PlayerMovement::dash(const Vec3& moveDir)
{
	//現在の速度を計算
	float speed = 1.0f + m_pPlayerParam->getAcceleration();

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//座標更新
	m_CylinderCoord.y -= moveDir.x * deltaTime;
	m_CylinderCoord.z += moveDir.z * m_Stats.m_DashSpeed * speed * deltaTime;
}

void PlayerMovement::convertCoord()
{
	//円筒座標をデカルト座標に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(m_CylinderCoord);

	//差を算出
	Vec3 diff = cartCoord - m_PrePosition;
	float sqrLength = diff.sqrLength();

	if (sqrLength > 0.0f)
	{
		RayHitResult result;
		if (getUser().getGameMediator()->getPhysicsManager()->raycastSingle(m_PrePosition, cartCoord, result))
		{
			if (!result.pHitObject->compareTag("Enemy"))
			{
				float distance = m_PrePosition.distance(result.hitPoint);
				if (distance < 0.1f)
					getTransform().setLocalPosition(m_PrePosition);

				return;
			}
		}
	}

	getTransform().setLocalPosition(cartCoord);
	m_pBoxCollider->getRigidBody()->activate(true);
}