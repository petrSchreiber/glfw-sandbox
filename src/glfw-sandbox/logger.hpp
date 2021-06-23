#pragma once

#include <string>

class logger
{
private:

public:
	
	//template<typename T>
	void info(std::string text);

	template<typename T>
	void error(T text);

	template<typename T>
	void warning(T text);

	template<typename T>
	void debug(T text);

};

