#pragma once
#include "Component/Utility/Action/AbstractAction.h"
#include "Component/Utility/Action/ActionManager.h"
#include "Component/Graphics/MeshRenderer.h"
#include "Math/Vec3.h"

namespace Action
{
	class TestPlayerAttackedEffect
		: public AbstractAction
	{
	protected:
		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual AbstractAction* clone() override;
	public:
		TestPlayerAttackedEffect(ActionManager* actionManager);
	private:
	    //�J�����̗h��̋���(1���)
		Vec3 cameraShakeStrengthFirst;
		//�J�����̗h��̋���(2���)
		Vec3 cameraShakeStrengthSecond;
		GameObject* m_pCameraObj;
		GameObject* pObjParticle;
		MeshRenderer* pRenderer;
	};
}
