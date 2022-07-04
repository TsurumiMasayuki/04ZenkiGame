#include "AccelBoard.h"
#include "Component/Physics/BoxColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>
#include "Component/Player/PlayerParamManager.h"

void AccelBoad::onStart()
{
	// ギミックとしてタグ付け
	getUser().setTag("Gimmick");

	// コライダー付与
	auto x = getUser().addComponent<BoxColiiderBt>();
	x->setTrigger(false);
	// 重力の無効化
	x->setUseGravity(false);

	// 実体をなくす
	getUser().getComponent<BoxColiiderBt>()->setTrigger(true);

	activeTimer.setMaxTime(3.0f);
}

void AccelBoad::onUpdate()
{
	Vec3 scale = getUser().getTransform().getLocalScale();
	Vec3 position = getUser().getTransform().getLocalPosition();
	Vec3 pPosition = targetObj->getTransform().getLocalPosition();

	// 加速させる
	if (!interval)
	{
		if (position.x - scale.x / 2 >= pPosition.x + 0.5f && position.x + scale.x / 2 >= pPosition.x - 0.5f &&
			position.y - scale.y / 2 >= pPosition.y + 0.5f && position.y + scale.y / 2 >= pPosition.y - 0.5f &&
			position.z - scale.z / 2 >= pPosition.z + 0.5f && position.z + scale.z / 2 >= pPosition.z - 0.5f)
		{
			// 移動量変化
			float pMoveSpeed = targetObj->getComponent<PlayerParamManager>()->getMoveSpeed();
			// 速度が一定以なら半分まで加速
			targetObj->getComponent<PlayerParamManager>()->setMoveSpeed(pMoveSpeed * acceleration);

			// 一時休止
			interval = true;

			// 休止タイマー開始
			activeTimer.reset();
		}
	}

	// 時間が経ったら戻す
	if (activeTimer.isTime())
	{
		interval = true;
	}

	// タイマーの更新
	activeTimer.update();
}
