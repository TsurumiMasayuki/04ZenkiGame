#pragma once
#include "Component\Base\AbstractComponent.h"

class PlayerHealth
	//AbstractComponent‚ğŒp³‚·‚é
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

private:
	int m_PlayerHP;
};