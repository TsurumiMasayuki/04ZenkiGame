#include "CoordConverter.h"
#include <cmath>

Vec3 CoordConverter::cartesianToCylinder(const Vec3& coord)
{
	float p = std::sqrtf(coord.x * coord.x + coord.y * coord.y);
	float phi = atan2f(coord.y, coord.x);

	return Vec3(p, phi, coord.z);
}

Vec3 CoordConverter::cylinderToCartesian(const Vec3& cylinder)
{
	float p = cylinder.x;
	float phi = cylinder.y;

	float x = p * std::cosf(phi);
	float y = p * std::sinf(phi);

	return Vec3(x, y, cylinder.z);
}
