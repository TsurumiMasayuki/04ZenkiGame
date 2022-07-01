#include "StageInfo.h"	
#include "Utility/StringUtility.h"
#include "Utility/CoordConverter.h"
#include "Utility/CylinderUtility.h"

void calcPosition(float radius, const nlohmann::json& json, std::vector<Vec3>& result)
{
	//配置パターンを取得
	std::string placementPattern = (std::string)json[1];

	//単体だった場合
	if (placementPattern == "Single")
	{
		//Z座標を取得
		float zPos = (float)json[3][0];
		//角度を取得
		float angle = MathUtility::toRadian((float)json[3][1]);

		//座標計算
		Vec3 position = CoordConverter::cylinderToCartesian(Vec3(radius, angle, zPos));

		result.emplace_back(position);
	}

	//直線だった場合
	if (placementPattern == "Line")
	{
		//始点
		float startZPos = (float)json[3][0];
		float startAngle = (float)json[3][1];

		//終点
		float endZPos = (float)json[4][0];
		float endAngle = (float)json[4][1];

		CylinderUtility::CalcPosLine(radius, startAngle, startZPos, endAngle, endZPos, (int)json[5], result);
	}
}

StageInfo::StageInfo(const nlohmann::json& file)
{
	//半径を取得
	m_Radius = 12.0f;

	//長さを取得
	m_Length = (float)file["stage"] * 2.0f;

	//オブジェクトリストを読み込み
	auto& objectList = file["objects"];

	//オブジェクトリストを走査
	for (auto& object : objectList)
	{
		//オブジェクト配置情報を作成
		auto& objectPlaceInfo = m_ObjectPlaceInfoList.emplace_back();

		//名前から.の後を切る
		std::string name = (std::string)object["name"];
		std::vector<std::string> split;
		StringUtility::split(name, '.', split);

		//オブジェクトの名前
		objectPlaceInfo.m_ObjectName = split.at(0);

		//transformを取得
		auto& transform = object["transform"];

		//オブジェクトの座標
		objectPlaceInfo.m_Position = Vec3(transform["translation"][0], transform["translation"][1], transform["translation"][2]);

		//円筒座標に変換
		Vec3 cylinder = CoordConverter::cartesianToCylinder(objectPlaceInfo.m_Position);

		//オブジェクトの円筒座標
		objectPlaceInfo.m_CylinderCoord = cylinder;

		//オブジェクトの角度
		objectPlaceInfo.m_Angles = Vec3(transform["rotation"][0], transform["rotation"][1], transform["rotation"][2]);

		//オブジェクトのスケール
		Vec3 scale = Vec3(transform["scaling"][0], transform["scaling"][1], transform["scaling"][2]);
		objectPlaceInfo.m_Scale = scale * 2.0f;
	}
}