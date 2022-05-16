#include "PlayerMovementFree.h"

#include "Actor/Base/GameObject.h"

#include "Component/Audio/AudioSource.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

#include "Component/Player/PlayerAttack.h"
#include "Component/Player/PlayerParamManager.h"

#include "Utility/JsonFileManager.h"

void PlayerMovementFree::onStart()
{
	m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
}

void PlayerMovementFree::onUpdate()
{
	//入力デバイスを取得
	const auto& input = GameDevice::getInput();

	//設定ファイルをホットリロード
	if (input.isKeyDown(DIK_R))
	{
		m_Stats = JsonFileManager<PlayerStats>::getInstance().get("PlayerStats");
	}

	//移動方向
	Vec3 moveDir = Vec3::zero();

	//入力に応じて移動方向をセット(マス目なので斜め移動はなし)
	//上
	if (input.isKey(DIK_UP))
		moveDir = Vec3(0.0f, 0.0f, 1.0f);
	//下
	if (input.isKey(DIK_DOWN))
		moveDir = Vec3(0.0f, 0.0f, -1.0f);
	//右
	if (input.isKey(DIK_RIGHT))
		moveDir = Vec3(1.0f, 0.0f, 0.0f);
	//左
	if (input.isKey(DIK_LEFT))
		moveDir = Vec3(-1.0f, 0.0f, 0.0f);

	//移動量がゼロなら実行しない
	if (moveDir.x == 0.0f && moveDir.z == 0.0f)
		return;

	dash(moveDir);
	move(moveDir);
}

void PlayerMovementFree::init(PlayerParamManager* pPlayerParam)
{
	m_pPlayerParam = pPlayerParam;
}

void PlayerMovementFree::move(const Vec3& moveDir)
{
	//ダッシュキーが押されているなら終了
	if (GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//移動量を算出
	Vec3 move = moveDir * m_Stats.m_WalkSpeed * deltaTime;

	//座標更新
	getTransform().setLocalPosition(getTransform().getLocalPosition() + move);
}

void PlayerMovementFree::dash(const Vec3& moveDir)
{
	//燃料がゼロなら実行しない
	if (m_pPlayerParam->isFuelZero())
		return;

	//ダッシュキーが押されていないなら終了
	if (!GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//加速度を取得
	float accel = 1.0f + m_pPlayerParam->getAcceleration();

	//deltaTimeを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//移動量を算出
	Vec3 move = moveDir * m_Stats.m_DashSpeed * accel * deltaTime;

	//座標更新
	getTransform().setLocalPosition(getTransform().getLocalPosition() + move);
}
