#include "PlayerMovement.h"
#include "Actor/Base/GameObject.h"
#include "Component/Utility/Action/Actions.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Device/GameDevice.h"
#include "Math/MathUtility.h"

#include "Component/Player/PlayerAttack.h"

using namespace Action;

void PlayerMovement::onStart()
{
	m_pActionManager = getUser().addComponent<ActionManager>();

	m_DashElapsedTime = 0.0f;
	m_DashMaxTime = 3.0f;
}

void PlayerMovement::onUpdate()
{
	//入力デバイスを取得
	const auto& input = GameDevice::getInput();

	//移動方向
	Vec3 moveDir = Vec3::zero();

	//入力に応じて移動方向をセット(マス目なので斜め移動はなし)
	//上
	if (input.isKey(DIK_UP))
		moveDir = Vec3(0.0f, 1.0f, 0.0f);
	//下
	if (input.isKey(DIK_DOWN))
		moveDir = Vec3(0.0f, -1.0f, 0.0f);
	//右
	if (input.isKey(DIK_RIGHT))
		moveDir = Vec3(1.0f, 0.0f, 0.0f);
	//左
	if (input.isKey(DIK_LEFT))
		moveDir = Vec3(-1.0f, 0.0f, 0.0f);

	//移動量がゼロなら実行しない
	if (moveDir.x == 0.0f && moveDir.y == 0.0f)
	{
		//ダッシュ経過時間をゼロにする
		m_DashElapsedTime = 0.0f;
		return;
	}

	dash(moveDir);
	move(moveDir);
}

void PlayerMovement::move(const Vec3& moveDir)
{
	//ダッシュキーが押されているなら終了
	if (GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//アニメーションの途中なら終了
	if (m_pActionManager->actionCount() > 0)
		return;

	//1マス移動
	m_pActionManager->enqueueAction(new EaseOutCubic(new MoveBy(moveDir, 0.25f)));
}

void PlayerMovement::dash(const Vec3& moveDir)
{
	//デルタタイムを取得
	float deltaTime = GameDevice::getGameTime().getDeltaTime();

	//ダッシュキーが押されているなら移動速度増加
	if (GameDevice::getInput().isKey(DIK_SPACE))
	{
		m_DashElapsedTime += deltaTime;
	}

	//ダッシュキーが押されていないなら終了
	if (!GameDevice::getInput().isKey(DIK_SPACE))
		return;

	//アニメーションの途中なら終了
	if (m_pActionManager->actionCount() > 0)
		return;

	//移動時間の割合を算出
	float moveTimeRatio = std::fmaxf(0.0f, 1.0f - m_DashElapsedTime / m_DashMaxTime);

	const Vec3& position = getUser().getTransform().getLocalPosition();

	//移動
	m_pActionManager->enqueueAction(new MoveBy(moveDir, 0.25f * moveTimeRatio));

	//攻撃用オブジェクトを生成
	auto pAttackObject = new GameObject(getUser().getGameMediator());
	//自身の座標を設定
	pAttackObject->getTransform().setLocalPosition(getUser().getTransform().getLocalPosition());
	//攻撃用コンポーネントをアタッチ
	pAttackObject->addComponent<PlayerAttack>();

	return;
}
