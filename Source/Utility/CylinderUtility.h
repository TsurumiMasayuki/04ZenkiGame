#pragma once
#include"Utility/CoordConverter.h"
#include"Math/MathUtility.h"
#include <vector>

class CylinderUtility final
{
public:
	static void CalcPosLine(float radius, float startAngle, float startZpos,
		float endAngle, float endZpos, int num, std::vector<Vec3>& result);

private:
	//コンストラクタを隠す
	CylinderUtility() {}
	//デストラクタを隠す
	~CylinderUtility() {}

	//代入演算子禁止
	void operator = (const CylinderUtility&) = delete;
	//コピーコンストラクタ禁止
	CylinderUtility(const CylinderUtility&) = delete;
};