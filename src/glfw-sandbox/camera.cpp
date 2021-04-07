#include "camera.hpp"
#include "glew.h"

void CameraManager::SetLocation(Vector3d vec) {
	location.x = vec.x;
	location.y = vec.y;
	location.z = vec.z;
}

void CameraManager::SetTarget(Vector3d vec) {
	target.x = vec.x;
	target.y = vec.y;
	target.z = vec.z;
}

void CameraManager::Apply() {
	gluLookAt(location.x, location.y, location.z,
			    target.x,   target.y,   target.z,
			           0,          1,          0);
}

std::string CameraManager::GetName() const {
	return name;
}
