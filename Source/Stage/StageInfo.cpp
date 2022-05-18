#include "StageInfo.h"	
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

		CalcPosLine(radius, startAngle, startZPos, endAngle, endZPos, (int)json[4], result);
	}
}

StageInfo::StageInfo(const nlohmann::json& file)
{
	//半径を取得
	m_Radius = file["CylinderRadius"];

	//長さを取得
	m_Length = file["CylinderLength"];

	//オブジェクトリストを読み込み
	auto& objectList = file["ObjectList"];

	//オブジェクトリストを走査
	for (auto& object : objectList)
	{
		//座標計算
		std::vector<Vec3> positions;
		calcPosition(m_Radius, object, positions);

		//出現位置
		float spawnPosZ = (float)object[2];

		//座標
		for (auto& position : positions)
		{
			//オブジェクト配置情報を作成
			auto& objectPlaceInfo = m_ObjectPlaceInfoList.emplace_back();

			//オブジェクトの名前
			objectPlaceInfo.m_ObjectName = (std::string)object[0];

			//オブジェクトの座標
			objectPlaceInfo.m_Position = position;

			//円筒座標に変換
			Vec3 cylinder = CoordConverter::cartesianToCylinder(position);

			//オブジェクトの円筒座標
			objectPlaceInfo.m_CylinderCoord = cylinder;

			//オブジェクトの角度
			objectPlaceInfo.m_Angle = MathUtility::toRadian(cylinder.y);

			//オブジェクトの出現位置(Z)
			objectPlaceInfo.m_SpawnPosZ = spawnPosZ;
		}
	}
}