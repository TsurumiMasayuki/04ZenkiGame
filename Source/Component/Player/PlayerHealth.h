#pragma once
#include "Component\Base\AbstractComponent.h"

class PlayerHealth
	//AbstractComponent���p������
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

private:
	int m_PlayerHP;
};