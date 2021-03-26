#pragma once

#include <chrono>

class Frame {
private:
	std::chrono::system_clock::duration timeBegin;
	std::chrono::system_clock::duration timeEnd;
public:
	Frame() {

	}

	void Begin();

	void End();

	float GetFrameRate();
};