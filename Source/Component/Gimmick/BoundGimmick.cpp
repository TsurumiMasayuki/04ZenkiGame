#include "BoundGimmick.h"
#include "Component/Physics/SphereColliderBt.h"
#include "Device/GameDevice.h"
#include "Utility/CoordConverter.h"
#include <Math/MathUtility.h>

void BoundGimmick::onStart()
{
	// 敵としてタグ付け
	getUser().setTag("Enemy");

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

	changeTime.update();
}
