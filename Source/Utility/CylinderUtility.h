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
	//�R���X�g���N�^���B��
	CylinderUtility() {}
	//�f�X�g���N�^���B��
	~CylinderUtility() {}

	//������Z�q�֎~
	void operator = (const CylinderUtility&) = delete;
	//�R�s�[�R���X�g���N�^�֎~
	CylinderUtility(const CylinderUtility&) = delete;
};