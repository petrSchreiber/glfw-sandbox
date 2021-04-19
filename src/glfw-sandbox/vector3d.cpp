#include "vector3d.hpp"

#include <cmath>

Vector3d Vector3d::operator+ (const Vector3d& other) {
	return Vector3d{ x + other.x, y + other.y, z + other.z };
}

Vector3d Vector3d::operator- (const Vector3d& other) {
	return Vector3d{ x - other.x, y - other.y, z - other.z };
}

Vector3d Vector3d::operator/ (float div) {
	float vectorLength = std::cbrt(x * x + y * y + z * z);

	return Vector3d{ x / vectorLength * 1 / div, y / vectorLength * 1 / div, z / vectorLength * 1 / div };
}

Vector3d Vector3d::operator* (float mul) {
	float vectorLength = std::cbrt(x * x + y * y + z * z);

	return Vector3d{ x / vectorLength * mul, y / vectorLength * mul, z / vectorLength * mul };
}
