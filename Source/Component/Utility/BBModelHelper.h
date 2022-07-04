#pragma once
#include "Blockbench/BlockbenchModel.h"
#include "Blockbench/BBInstanceInfo.h"
#include "Component/Base/AbstractComponent.h"
#include "Utility/InstancedRendererHelper.h"


class BBModelHelper
	: public AbstractComponent
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;

	void setRenderer(InstancedRendererHelper<BBInstanceInfo>* pInstancedRendererHelper);

private:
	BlockbenchModel* m_pBBModel;
	InstancedRendererHelper<BBInstanceInfo>* m_pInstancedRendererHelper;
};