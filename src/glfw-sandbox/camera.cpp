#include "camera.hpp"
#include "glew.h"

void Camera::SetLocation(Vector3d vec) {
	location.x = vec.x;
	location.y = vec.y;
	location.z = vec.z;
}

void Camera::SetTarget(Vector3d vec) {
	target.x = vec.x;
	target.y = vec.y;
	target.z = vec.z;
}

void Camera::Apply() {
	gluLookAt(location.x, location.y, location.z,
			    target.x,   target.y,   target.z,
			           0,          1,          0);
}
