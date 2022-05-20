#pragma once
#include <vector>
#include "json.hpp"
#include "Math/Vec3.h"

struct ObjectPlaceInfo
{
	//�ݒu����I�u�W�F�N�g��
	std::string m_ObjectName;
	//���W
	Vec3 m_Position;
	//�~�����W
	Vec3 m_CylinderCoord;
	//�p�x
	float m_Angle;
	//�o���ʒu
	float m_SpawnPosZ;
};

struct StageInfo
{
	StageInfo(const nlohmann::json& file);

	//���a
	float m_Radius;
	//����
	float m_Length;
	//�I�u�W�F�N�g�z�u��񃊃X�g
	std::vector<ObjectPlaceInfo> m_ObjectPlaceInfoList;
};