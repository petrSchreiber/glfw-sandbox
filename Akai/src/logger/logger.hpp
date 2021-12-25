#pragma once

#include <string>

// work in progres, adding some basic stuff at the moment
// https://github.com/gabime/spdlog

class logger
{
private:

public:
	
	void trace(const std::string& text);

	void debug(const std::string& text);
	
	void info(const std::string& text);

	void warning(const std::string& text);

	void error(const std::string& text);

	void critical(const std::string& text);

};


