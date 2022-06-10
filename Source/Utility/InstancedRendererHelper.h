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

	//�C���X�^���X�p����A������(Transpose�s�v)
	void appendInstanceInfo(const std::vector<DirectX::XMMATRIX>& objMatrices);
	//�C���X�^���X�p����Renderer�ɓ]��
	void sendInstanceInfo();

private:
	//�I�u�W�F�N�g���Ƃ̃f�[�^
	std::vector<DirectX::XMMATRIX> m_DataPerObject;
	//�`�悷��InstancedRenderer
	InstancedRenderer<T>* m_pInstancedRenderer;

	//Blockbench���f��
	const BlockbenchModel* m_pBBModel;
	//Blockbench���f���p�}�e���A��
	BBModelMaterial* m_pMaterial;

	//�O�t���[���̃I�u�W�F�N�g��
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
	//�C���X�^���V���O�p����A��
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

	//�O�t���[���̃I�u�W�F�N�g���Ɣ�r���Ĉ���Ă�����X�V
	if (currentObjectCount != m_PreviousObjectCount)
	{
		m_pMaterial->setModelCount(currentObjectCount);

		m_pMaterial->initDataPerCube();
		m_pMaterial->initDataPerObject();
	}

	//�}�e���A���Ƀf�[�^���M
	m_pMaterial->updateDataPerObject(m_DataPerObject);

	m_pInstancedRenderer->setInstanceCount(currentObjectCount * m_pBBModel->getCubeCount());

	m_DataPerObject.clear();

	m_PreviousObjectCount = currentObjectCount;
}