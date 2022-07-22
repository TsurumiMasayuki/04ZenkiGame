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

	m_ObjectPlaceInfoList.resize(objectList.size());

	//オブジェクトリストを走査
	for (int i = 0; i < m_ObjectPlaceInfoList.size(); i++)
	{
		//オブジェクト配置情報を作成
		const auto& object = objectList[i];
		auto& objectPlaceInfo = m_ObjectPlaceInfoList.at(i);

		//名前から.の後を切る
		std::string name = (std::string)object["name"];
		std::vector<std::string> split;
		StringUtility::split(name, '.', split);

		//オブジェクトの名前
		objectPlaceInfo.m_ObjectName = split.at(0);

		//transformを取得
		const auto& transform = object["transform"];

		const auto& position = transform["translation"];

		float posX = std::stof((std::string)(position[0]));
		float posY = std::stof((std::string)(position[1]));
		float posZ = std::stof((std::string)(position[2]));

		//オブジェクトの座標
		objectPlaceInfo.m_Position = Vec3(posX,
			posY,
			posZ
		);

		//円筒座標に変換
		Vec3 cylinder = CoordConverter::cartesianToCylinder(objectPlaceInfo.m_Position);

		//オブジェクトの円筒座標
		objectPlaceInfo.m_CylinderCoord = cylinder;

		const auto& rotation = transform["rotation"];

		float rotX = std::stof((std::string)(rotation[0]));
		float rotY = std::stof((std::string)(rotation[1]));
		float rotZ = std::stof((std::string)(rotation[2]));

		if (objectPlaceInfo.m_ObjectName == "GarssBlock")
		{
			rotX = 0.0f;
			rotY = std::stof((std::string)(rotation[1]));
			rotZ = std::stof((std::string)(rotation[2]));
		}

		//オブジェクトの角度
		objectPlaceInfo.m_Angles = Vec3(rotX,
			rotY,
			rotZ
		);

		const auto& scale = transform["scaling"];

		float scaleX = std::stof((std::string)(scale[0]));
		float scaleY = std::stof((std::string)(scale[1]));
		float scaleZ = std::stof((std::string)(scale[2]));

		if (objectPlaceInfo.m_ObjectName == "GarssBlock")
		{
			scaleY = std::stof((std::string)(scale[2]));
			scaleZ = std::stof((std::string)(scale[1]));
		}

		//オブジェクトのスケール
		objectPlaceInfo.m_Scale = Vec3(scaleX, scaleY, scaleZ) * 2.0f;
	}
}