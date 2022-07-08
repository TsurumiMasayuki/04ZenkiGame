#include "StageInfo.h"	
#include "Utility/StringUtility.h"
#include "Utility/CoordConverter.h"
#include "Utility/CylinderUtility.h"

void calcPosition(float radius, const nlohmann::json& json, std::vector<Vec3>& result)
{
	//�z�u�p�^�[�����擾
	std::string placementPattern = (std::string)json[1];

	//�P�̂������ꍇ
	if (placementPattern == "Single")
	{
		//Z���W���擾
		float zPos = (float)json[3][0];
		//�p�x���擾
		float angle = MathUtility::toRadian((float)json[3][1]);

		//���W�v�Z
		Vec3 position = CoordConverter::cylinderToCartesian(Vec3(radius, angle, zPos));

		result.emplace_back(position);
	}

	//�����������ꍇ
	if (placementPattern == "Line")
	{
		//�n�_
		float startZPos = (float)json[3][0];
		float startAngle = (float)json[3][1];

		//�I�_
		float endZPos = (float)json[4][0];
		float endAngle = (float)json[4][1];

		CylinderUtility::CalcPosLine(radius, startAngle, startZPos, endAngle, endZPos, (int)json[5], result);
	}
}

StageInfo::StageInfo(const nlohmann::json& file)
{
	//���a���擾
	m_Radius = 12.0f;

	//�������擾
	m_Length = (float)file["stage"] * 2.0f;

	//�I�u�W�F�N�g���X�g��ǂݍ���
	auto& objectList = file["objects"];

	m_ObjectPlaceInfoList.resize(objectList.size());

	//�I�u�W�F�N�g���X�g�𑖍�
	for (int i = 0; i < m_ObjectPlaceInfoList.size(); i++)
	{
		//�I�u�W�F�N�g�z�u�����쐬
		const auto& object = objectList[i];
		auto& objectPlaceInfo = m_ObjectPlaceInfoList.at(i);

		//���O����.�̌��؂�
		std::string name = (std::string)object["name"];
		std::vector<std::string> split;
		StringUtility::split(name, '.', split);

		//�I�u�W�F�N�g�̖��O
		objectPlaceInfo.m_ObjectName = split.at(0);

		//transform���擾
		const auto& transform = object["transform"];

		//�I�u�W�F�N�g�̍��W
		objectPlaceInfo.m_Position = Vec3(transform["translation"][0], transform["translation"][1], transform["translation"][2]);

		//�~�����W�ɕϊ�
		Vec3 cylinder = CoordConverter::cartesianToCylinder(objectPlaceInfo.m_Position);

		//�I�u�W�F�N�g�̉~�����W
		objectPlaceInfo.m_CylinderCoord = cylinder;

		//�I�u�W�F�N�g�̊p�x
		objectPlaceInfo.m_Angles = Vec3(transform["rotation"][0], transform["rotation"][1], transform["rotation"][2]);

		//�I�u�W�F�N�g�̃X�P�[��
		Vec3 scale = Vec3(transform["scaling"][0], transform["scaling"][1], transform["scaling"][2]);
		objectPlaceInfo.m_Scale = scale * 2.0f;
	}
}