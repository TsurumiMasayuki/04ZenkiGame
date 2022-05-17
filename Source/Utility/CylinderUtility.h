#pragma once
#include"Utility/CoordConverter.h"
#include"Math/MathUtility.h"
#include <vector>

static void CalcPosLine(float radius,float startAngle,float startZpos,
	float endAngle,float endZpos,int num,std::vector<Vec3>& result);