#pragma once

#include "vector3d.hpp"
#include <string>

class CameraManager {
private:
	const std::string name;
	Vector3d location{0,1.7,0};
	Vector3d target{0,1.7,-1};
	float fov = 60;
public:

	CameraManager(std::string cameraName, Vector3d location) : name{cameraName}, location { location } {

	}

	void SetLocation(Vector3d vec);

	void SetTarget(Vector3d vec);

	void Apply();

	std::string GetName() const;
};