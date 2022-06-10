#pragma once
#include <vector>
#include "Component/Graphics/InstancedRenderer.h"
#include "Math/Vec3.h"
#include "Utility/Color.h"

#include "Blockbench\BlockbenchModel.h"
#include "Graphics\Material\BBModelMaterial.h"

template<typename T> class InstancedRendererHelper
{
public:
	InstancedRendererHelper(const BlockbenchModel* pModel, InstancedRenderer<T>* pInstancedRenderer);
	~InstancedRendererHelper();

	//インスタンス用情報を連結する(Transpose不要)
	void appendInstanceInfo(const std::vector<DirectX::XMMATRIX>& objMatrices);
	//インスタンス用情報をRendererに転送
	void sendInstanceInfo();

private:
	//オブジェクトごとのデータ
	std::vector<DirectX::XMMATRIX> m_DataPerObject;
	//描画するInstancedRenderer
	InstancedRenderer<T>* m_pInstancedRenderer;

	//Blockbenchモデル
	const BlockbenchModel* m_pBBModel;
	//Blockbenchモデル用マテリアル
	BBModelMaterial* m_pMaterial;

	//前フレームのオブジェクト数
	int m_PreviousObjectCount;
};

template<typename T>
inline InstancedRendererHelper<T>::InstancedRendererHelper(const BlockbenchModel* pModel, InstancedRenderer<T>* pInstancedRenderer)
{
	m_pMaterial->init(DX12GraphicsCore::g_pDevice.Get());
	m_pMaterial->setBBModel(*pModel);
	m_pInstancedRenderer->setMaterial(m_pMaterial);
}

template<typename T>
inline InstancedRendererHelper<T>::~InstancedRendererHelper()
{
	if (m_pMaterial != nullptr)
		delete m_pMaterial;
}

template<typename T>
inline void InstancedRendererHelper<T>::appendInstanceInfo(const std::vector<DirectX::XMMATRIX>& objMatrices)
{
	//インスタンシング用情報を連結
	for (const auto& matrix : objMatrices)
	{
		m_DataPerObject.emplace_back(matrix);
	}
}

template<typename T>
inline void InstancedRendererHelper<T>::sendInstanceInfo()
{
	int currentObjectCount = (int)m_DataPerObject.size();

	if (currentObjectCount == 0) return;

	//前フレームのオブジェクト数と比較して違っていたら更新
	if (currentObjectCount != m_PreviousObjectCount)
	{
		m_pMaterial->setModelCount(currentObjectCount);

		m_pMaterial->initDataPerCube();
		m_pMaterial->initDataPerObject();
	}

	//マテリアルにデータ送信
	m_pMaterial->updateDataPerObject(m_DataPerObject);

	m_pInstancedRenderer->setInstanceCount(currentObjectCount * m_pBBModel->getCubeCount());

	m_DataPerObject.clear();

	m_PreviousObjectCount = currentObjectCount;
}