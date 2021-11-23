#include <cstdint>
#include <GLFW/glfw3.h>



class akaiWindow
{
public:
	void akaiWindowInit();

	void akaiWindowMainLoop();

	GLFWwindow* akaiGetWindow();

	bool akaiWindowOpen();

	void akaiWindowCleanup();
	

private:

	GLFWwindow* window;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	

};

