#pragma once
#include "Math/Vec3.h"

//座標変換補助
class CoordConverter final
{
public:
	//デカルト座標系を円筒座標系に変換
	static Vec3 cartesianToCylinder(const Vec3& coord);

	//円筒座標系をデカルト座標系に変換
	static Vec3 cylinderToCartesian(const Vec3& cylinder);

private:
	//コンストラクタを隠す
	CoordConverter() {}
	//デストラクタを隠す
	~CoordConverter() {}

	//代入演算子禁止
	void operator = (const CoordConverter&) = delete;
	//コピーコンストラクタ禁止
	CoordConverter(const CoordConverter&) = delete;
};