#pragma once
#include "Scene/Base/AbstractScene.h"
#include "Component/Base/AbstractComponent.h"
#include "Component/Graphics/GUI/GUISpriteRenderer.h"
#include "Actor/Base/GameObject.h"
class ClearScene :public AbstractScene
{
public:

	virtual std::string nextScene() override;
	virtual bool isEnd() override;
	virtual void start() override;
	virtual void update() override;
	virtual void shutdown() override;
private:
	GameObject* ClearObject;
	GUISpriteRenderer* ClearSprite;

};