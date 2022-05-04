#pragma once
#include "Component/Utility/Action/AbstractAction.h"

namespace Action
{
	class TestFlameEffect
		: public AbstractAction
	{
		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual AbstractAction* clone() override;
	};
}


