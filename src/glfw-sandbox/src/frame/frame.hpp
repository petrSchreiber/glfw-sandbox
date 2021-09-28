#pragma once

#include <chrono>

class Frame {
private:

	std::chrono::steady_clock::duration timeBegin;
	std::chrono::steady_clock::duration timeEnd;

	double framerate = 5000;
public:
	Frame() {

	}

	void Begin();

	void End();

	double GetFrameRate();

};