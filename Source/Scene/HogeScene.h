#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Map/GoalObject.h"

class DX12Mesh;

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
	DX12Mesh* m_pCube;
	GoalObject* goalObject= nullptr;
};