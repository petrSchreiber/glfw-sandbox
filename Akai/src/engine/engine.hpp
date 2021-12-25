#include "logger/logger.hpp"


class WindowCreator
{
private:
	logger WinLog;

	int resWidth{};
	int resHeight{};
	
	char *title;
	GLFWmonitor *monitor;
	GLFWwindow *share;

	int fieldOfView{};

	void opengl_intialize() {
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
		glMatrixMode(GL_PROJECTION);					  // Switch to Projection-Matrix mode.
		glLoadIdentity();								  // Reset the Projection-Matrix.

		gluPerspective(fieldOfView, resWidth / (double)resHeight, 0.09, 25);

		glMatrixMode(GL_MODELVIEW);						  // Select the Modelview-Matrix
	}

public:

	WindowCreator(int resW, int resH, int fov) 
		: resWidth{ resW }, resHeight{ resH }, fieldOfView{fov}
	{
		if (!glfwInit())
		{
			WinLog.error("Failed to initialize GLFW library");
		}
		
		if (!glfwVulkanSupported())
		{
			WinLog.error("Vulkan not supported");
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
		}

		// Needed before GLEW
		glfwMakeContextCurrent(window);

		// Get the latest GL, yeaaah!
		int err = glewInit();
		if (GLEW_OK != err)
		{
			std::cout << "Failed to initialize GLEW library: " << glewGetErrorString(err) << std::endl;
		}		

		// Initialize OpenGL defaults
		opengl_intialize();

		return window;
	}
};

