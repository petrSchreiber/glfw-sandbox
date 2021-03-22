#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>

class Controls
{
private:
	
	GLFWwindow *window;
	int state = 0;

public:

	Controls(GLFWwindow* window)
		: window{window}
	{
		std::cout << "Test" << std::endl;
	};

	bool arrowUP()
	{
	state = glfwGetKey(window, GLFW_KEY_UP);
	if (state == GLFW_PRESS)
		return true;
	
	return false;
	}

	bool arrowDOWN()
	{
		state = glfwGetKey(window, GLFW_KEY_DOWN);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	bool arrowLEFT()
	{
		state = glfwGetKey(window, GLFW_KEY_LEFT);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	bool arrowRIGHT()
	{
		state = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	bool keyC()
	{
		state = glfwGetKey(window, GLFW_KEY_C);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	bool keyT()
	{
		state = glfwGetKey(window, GLFW_KEY_T);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

};

