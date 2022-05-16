#pragma once
#include "Math/Vec3.h"

//���W�ϊ��⏕
class CoordConverter final
{
public:
	//�f�J���g���W�n���~�����W�n�ɕϊ�
	static Vec3 cartesianToCylinder(const Vec3& coord);

	//�~�����W�n���f�J���g���W�n�ɕϊ�
	static Vec3 cylinderToCartesian(const Vec3& cylinder);

private:
	//�R���X�g���N�^���B��
	CoordConverter() {}
	//�f�X�g���N�^���B��
	~CoordConverter() {}

	//������Z�q�֎~
	void operator = (const CoordConverter&) = delete;
	//�R�s�[�R���X�g���N�^�֎~
	CoordConverter(const CoordConverter&) = delete;
};