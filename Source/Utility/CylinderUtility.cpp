#include "CylinderUtility.h"

void CalcPosLine(float radius, float startAngle, float startZpos, 
	float endAngle, float endZpos, int num, std::vector<Vec3>& result)
{
	float angleIncrement = endAngle - startAngle / num;
	float radianStart = MathUtility::toRadian(startAngle);
	float radianEnd = MathUtility::toRadian(endAngle);
	Vec3 cylinderStart = Vec3{ radius,radianStart,startZpos };
	Vec3 cylinderEnd = Vec3{ radius,radianEnd,endZpos };
	for (int i = 0; i < num; i++)
	{
		float baffer = angleIncrement * i;
		Vec3 lerped = Vec3::lerp(cylinderStart, cylinderEnd, baffer / endAngle-startAngle);
		Vec3 pos = CoordConverter::cylinderToCartesian(lerped);
		result.push_back(pos);
	}
}
