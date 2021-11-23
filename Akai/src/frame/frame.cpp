#include "frame.hpp"
#include <chrono>

/*
* Notes: We could also consider using glfwGetTime();
*/

void Frame::Begin() {
	timeBegin = std::chrono::high_resolution_clock::now().time_since_epoch();
}

void Frame::End() {
	timeEnd = std::chrono::high_resolution_clock::now().time_since_epoch();
	framerate = 1 / ((double)std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin).count() / 1000000.0);
}

double Frame::GetFrameRate() {
	return framerate;
}
