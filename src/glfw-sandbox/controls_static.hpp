#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>



class ControlsStatic
{
private:

	bool test = false;

	
public:




	static bool arrowUP(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_UP);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	static bool arrowDOWN(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_DOWN);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	static bool arrowLEFT(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_LEFT);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	static bool arrowRIGHT(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	static bool keyC(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_C);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	static bool keyT(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_T);
		if (state == GLFW_PRESS)
			return true;

		return false;
	}

	static bool keyF(GLFWwindow* window)
	{
		int state{};
		state = glfwGetKey(window, GLFW_KEY_F);
		
		if (state == GLFW_PRESS)	
			return true;
	
		return false;
	}

	 static bool keyR(GLFWwindow* window)
	{	
		
		glfwSetKeyCallback(window, key_callback);
		return false;
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		if (key == GLFW_KEY_R)
		{
			switch (action)
			{
			case GLFW_RELEASE:
			{
				std::cout << "R key released" << std::endl;;
				break;
			}
			default:
			{
				//ControlsStatic::test = false;
				break;

			}
			}
		}



	}
	
		
	

};

