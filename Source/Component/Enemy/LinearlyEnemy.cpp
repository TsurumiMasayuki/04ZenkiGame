#include "LinearlyEnemy.h"
#include "Device/GameDevice.h"

void LinearlyEnemy::onStart()
{
	// それぞれ座標初期化
	position = Vec3(0, 0, 0);
	speed = 1.0f;
	targetPos = Vec3(0, 0, 0);

	moveTimer.setMaxTime(3.0f);
	easingTimer.setMaxTime(1.0f);
}

void LinearlyEnemy::onUpdate()
{
	// 基準座標取得
	position = getUser().getTransform().getLocalPosition();

	// 目標座標取得
	targetPos = object->getTransform().getLocalPosition();

	// 移動中
	if (canMove)
	{
		// 座標更新
		position += moveVec * speed * GameDevice::getGameTime().getDeltaTime();
		// 座標セット
		getUser().getTransform().setLocalPosition(position);
	}
	// 停止中
	else
	{
		// 何もしない
	}
	
	// 移動、停止の切り替え
	if (moveTimer.isTime())
	{
		canMove = !canMove;

		if (canMove)
		{
			moveTimer.setMaxTime(moveTime);
			moveTimer.reset();
		}
		else
		{
			moveTimer.setMaxTime(stopTime);
			moveTimer.reset();
		}
	}

	moveTimer.update();
}

void LinearlyEnemy::SetTarget(GameObject* object)
{
	this->object = object;
}

Vec3 LinearlyEnemy::DecideDir()
{
	// 移動方向算出
	Vec3 result = targetPos - position;
	result.normalized();
	return result;
}
