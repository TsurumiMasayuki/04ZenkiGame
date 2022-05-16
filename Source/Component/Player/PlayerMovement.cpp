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

#include "Utility/JsonFileManager.h"
#include "Utility/CoordConverter.h"

using namespace Action;

void PlayerMovement::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");

	m_CylinderCoord.z = getTransform().getLocalPosition().z;
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

	dash(moveDir);
	move(moveDir);
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
	//ダッシュボタンが押されているなら終了
	if (GameInput::getInstance().getPlayerDash())
		return;

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
	//燃料がゼロなら実行しない
	if (m_pPlayerParam->isFuelZero())
		return;

	//ダッシュボタンが押されていないなら終了
	if (!GameInput::getInstance().getPlayerDash())
		return;

	//現在の速度を計算
	float speed = 1.0f + m_pPlayerParam->getAcceleration();

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//座標更新
	m_CylinderCoord.y -= moveDir.x * deltaTime;
	m_CylinderCoord.z += moveDir.z * speed * deltaTime;
}

void PlayerMovement::convertCoord()
{
	//円筒座標をデカルト座標に変換
	Vec3 cartCoord = CoordConverter::cylinderToCartesian(m_CylinderCoord);

	//座標を適用
	getTransform().setLocalPosition(cartCoord);

	//回転(Z)
	getTransform().setLocalAngleZ(MathUtility::toDegree(m_CylinderCoord.y));
}