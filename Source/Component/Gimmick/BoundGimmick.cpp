#include "BoundGimmick.h"
#include "Component/Physics/SphereColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>
#include "Component/Player/PlayerParamManager.h"

void BoundGimmick::onStart()
{
	// ギミックとしてタグ付け
	getUser().setTag("Gimmick");

	// コライダー付与
	auto x = getUser().addComponent<SphereColliderBt>();
	x->setTrigger(false);
	// 重力の無効化
	x->setUseGravity(false);

	changeTime.setMaxTime(3.0f);
}

void BoundGimmick::onUpdate()
{
	// 時間が来たら切り替える
	if (changeTime.isTime())
	{
		isExpansion = !isExpansion;
	}

	// 膨らむ
	if (isExpansion)
	{
		scale = Vec3(3, 3, 3);
	}
	else
	{
		scale = Vec3(1, 1, 1);
	}

	// 跳ね返す
	if (getUser().getTransform().getLocalPosition().distance(targetObj->getTransform().getLocalPosition()) < scale.x)
	{
		// 移動方向反転
		Vec3 pMoveDir = targetObj->getComponent<PlayerParamManager>()->getMoveDir();
		targetObj->getComponent<PlayerParamManager>()->setMoveDir(-pMoveDir);
	}

	// サイズセット
	getUser().getTransform().setLocalScale(scale);

	changeTime.update();
}
