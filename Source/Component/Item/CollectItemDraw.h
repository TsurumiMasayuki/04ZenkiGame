#pragma once
#include "Blockbench/BBInstanceInfo.h"
#include "Blockbench/BlockbenchLoader.h"
#include "Utility/InstancedRendererHelper.h"
#include "CollectItemUI.h"
#include "Scene/HogeScene.h"

//描画部分
class CollectItemUI;
class BBModelMaterial;
class CollectItemDraw : 
    public AbstractComponent
{
public:
    virtual void onStart() override;
    virtual void onUpdate() override;
private:
    std::unordered_map<std::string, InstancedRendererHelper<BBInstanceInfo>*> m_RenderHelpers;
    BlockbenchLoader star_blockModelLoader;
    DX12Mesh* m_pCube;
    GameObject* GameObj;
    CollectItemUI* CollectItemUIObj;
};

