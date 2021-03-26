#include "frame.hpp"
#include <chrono>

/*
* Notes: We could also consider using glfwGetTime();
*/

void Frame::Begin() {
	timeBegin = std::chrono::system_clock::now().time_since_epoch();
}

void Frame::End() {
	timeEnd = std::chrono::system_clock::now().time_since_epoch();
}

float Frame::GetFrameRate() {
	return 1/((float)std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin).count() / 1000.0f);
}
