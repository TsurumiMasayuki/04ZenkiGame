#include "StageInfo.h"	
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

		CalcPosLine(radius, startAngle, startZPos, endAngle, endZPos, (int)json[4], result);
	}
}

StageInfo::StageInfo(const nlohmann::json& file)
{
	//���a���擾
	m_Radius = file["CylinderRadius"];

	//�������擾
	m_Length = file["CylinderLength"];

	//�I�u�W�F�N�g���X�g��ǂݍ���
	auto& objectList = file["ObjectList"];

	//�I�u�W�F�N�g���X�g�𑖍�
	for (auto& object : objectList)
	{
		//���W�v�Z
		std::vector<Vec3> positions;
		calcPosition(m_Radius, object, positions);

		//�o���ʒu
		float spawnPosZ = (float)object[2];

		//���W
		for (auto& position : positions)
		{
			//�I�u�W�F�N�g�z�u�����쐬
			auto& objectPlaceInfo = m_ObjectPlaceInfoList.emplace_back();

			//�I�u�W�F�N�g�̖��O
			objectPlaceInfo.m_ObjectName = (std::string)object[0];

			//�I�u�W�F�N�g�̍��W
			objectPlaceInfo.m_Position = position;

			//�~�����W�ɕϊ�
			Vec3 cylinder = CoordConverter::cartesianToCylinder(position);

			//�I�u�W�F�N�g�̉~�����W
			objectPlaceInfo.m_CylinderCoord = cylinder;

			//�I�u�W�F�N�g�̊p�x
			objectPlaceInfo.m_Angle = MathUtility::toRadian(cylinder.y);

			//�I�u�W�F�N�g�̏o���ʒu(Z)
			objectPlaceInfo.m_SpawnPosZ = spawnPosZ;
		}
	}
}