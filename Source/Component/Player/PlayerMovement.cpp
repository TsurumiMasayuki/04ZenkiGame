#include "PlayerMovement.h"
#include "Actor/Base/GameObject.h"

#include "Component/Audio/AudioSource.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerParamManager.h"

#include "Device/GameInput.h"

#include "Effect/TestFlameEffect.h"

#include "Utility/JsonFileManager.h"
#include "Utility/CoordConverter.h"

using namespace Action;

void PlayerMovement::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");

	m_CylinderCoord.z = getTransform().getLocalPosition().z;

	m_pActionManager = getUser().getComponent<Action::ActionManager>();
}

void PlayerMovement::onUpdate()
{
	//入力デバイスを取得
	const auto& input = GameDevice::getInput();

	//設定ファイルをホットリロード
	if (input.isKeyDown(DIK_R))
	{
		m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
	}

	//移動方向
	Vec3 moveDir = GameInput::getInstance().getPlayerMove();

	moveDir.z = std::fmaxf(0.0f, moveDir.z);

	//ダッシュボタンが押されているなら&燃料がゼロでないなら
	if (GameInput::getInstance().getPlayerDash() &&
		!m_pPlayerParam->isFuelZero())
	{
		//if (m_pActionManager->actionCount() == 0)
		//{
		//	//間隔を開けて火炎エフェクト
		//	auto pSequence = new Action::Sequence(
		//		{
		//			new Action::TestFlameEffect(m_pActionManager),
		//			new Action::WaitForSeconds(0.1f)
		//		}
		//	);

		//	//リピート実行
		//	auto pRepeat = new Action::RepeatForever(pSequence);

		//	m_pActionManager->enqueueAction(pRepeat);
		//}
		dash(moveDir);
	}
	else
	{
		////エフェクト停止
		//m_pActionManager->forceNext();
		move(moveDir);
	}

	convertCoord();
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

	//座標を適用
	getTransform().setLocalPosition(cartCoord);

	//回転(Z)
	getTransform().setLocalAngleZ(MathUtility::toDegree(m_CylinderCoord.y) - 90.0f);
}