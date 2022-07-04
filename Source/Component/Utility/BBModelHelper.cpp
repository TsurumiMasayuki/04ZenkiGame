#include "BBModelHelper.h"

void BBModelHelper::onStart()
{
}

void BBModelHelper::onUpdate()
{
	m_pInstancedRendererHelper->appendInstanceInfo(getUser().getTransform().getWorldMatrix());
}

void BBModelHelper::setRenderer(InstancedRendererHelper<BBInstanceInfo>* pInstancedRendererHelper)
{
	m_pInstancedRendererHelper = pInstancedRendererHelper;
}