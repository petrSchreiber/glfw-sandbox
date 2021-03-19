#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Will give use GLFW + GL

#include <iostream>


class windowCreator
{
private:
	int resWidth{};
	int resHeight{};
	char *title;
	GLFWmonitor *monitor;
	GLFWwindow *share;

	int fieldOfView{};


public:

	windowCreator(int resW, int resH, int fov) // for now leave other values and hardcode like a noob, Petr help <3 :D
		: resWidth{ resW }, resHeight{ resH }, fieldOfView{fov}
	{	
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW library" << std::endl;
			//return 1;
		}			
	};

	auto getWindow() { 

		GLFWwindow* window;
		window = glfwCreateWindow(resWidth, resHeight,				// Resolution
			"Having problems with this one in constructor",         // Title
			NULL,													// Monitor for fullscreen
			NULL);													// Window to steal OpenGL context from - in most cases NULL

		if (!window)
		{
			std::cout << "Failed to initialize GLFW window" << std::endl;
			glfwTerminate();
			//return 2; Why I can't return 2?
		}

		return window;

	}

	void opengl_intialize() { //int resWidth, int resHeight, int fov
		// Depth
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glClearDepth(1.0);

		// Color
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		// Lighting
		glEnable(GL_NORMALIZE);
		glEnable(GL_AUTO_NORMAL);
		glShadeModel(GL_SMOOTH);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

		// Texture related
		glPixelStorei(GL_PACK_ALIGNMENT, 1);

		// Blending
		glBlendFunc(GL_ONE, GL_ONE);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glViewport(0, 0, resWidth, resHeight);            // Set viewport region.
		glMatrixMode(GL_PROJECTION);                // Switch to Projection-Matrix mode.
		glLoadIdentity();                           // Reset the Projection-Matrix.

		gluPerspective(fieldOfView, resWidth / (double)resHeight, 0.09, 25);

		glMatrixMode(GL_MODELVIEW);                 // Select the Modelview-Matrix
	}


};

