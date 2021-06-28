#pragma once

#include <string>

// work in progres, adding some basic stuff at the moment
// https://github.com/gabime/spdlog

class logger
{
private:

public:
	
	void trace(std::string text);

	void debug(std::string text);
	
	void info(std::string text);

	void warning(std::string text);

	void error(std::string text);

	void critical(std::string text);

};


