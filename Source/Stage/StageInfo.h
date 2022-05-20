#pragma once
#include <vector>
#include "json.hpp"
#include "Math/Vec3.h"

struct ObjectPlaceInfo
{
	//設置するオブジェクト名
	std::string m_ObjectName;
	//座標
	Vec3 m_Position;
	//円筒座標
	Vec3 m_CylinderCoord;
	//角度
	float m_Angle;
	//出現位置
	float m_SpawnPosZ;
};

struct StageInfo
{
	StageInfo(const nlohmann::json& file);

	//半径
	float m_Radius;
	//長さ
	float m_Length;
	//オブジェクト配置情報リスト
	std::vector<ObjectPlaceInfo> m_ObjectPlaceInfoList;
};