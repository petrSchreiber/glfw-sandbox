#pragma once

#include <cmath>

class Vector3d {
public:
	float x;
	float y;
	float z;

	Vector3d(float x, float y, float z) : x{ x }, y{ y }, z{ z } {
	}

	Vector3d operator+ (const Vector3d& other);

	Vector3d operator- (const Vector3d& other);

	Vector3d operator/ (float div);
};