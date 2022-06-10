#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Map/GoalObject.h"

class StageLoader;

class HogeScene
	: public AbstractScene
{
public:
	virtual std::string nextScene() override;
	virtual bool isEnd() override;
	virtual void start() override;
	virtual void update() override;
	virtual void shutdown() override;

private:
	GoalObject* goalObject= nullptr;
	StageLoader* m_pStageLoader;
};