#pragma once

#include "vector3d.hpp"

class Camera {
private:
	Vector3d location{0,1.7,0};
	Vector3d target{0,1.7,-1};
	float fov = 60;
public:

	void SetLocation(Vector3d vec);

	void SetTarget(Vector3d vec);

	void Apply();
};