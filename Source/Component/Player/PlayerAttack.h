#pragma once
#include "Component/Base/AbstractComponent.h"
#include "Utility/Timer.h"

namespace Action
{
	class ActionManager;
}

//プレイヤー//攻撃判定用コンポーネント
class PlayerAttack
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

protected:
	virtual void onCollisionEnter(GameObject* pHit) override;

private:
	//カメラにアタッチされているActionManager
	Action::ActionManager* m_pCameraActionManager;
};