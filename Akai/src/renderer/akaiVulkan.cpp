
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vulkan/vulkan.h>



class akaiVulkan
{
public:
    void initialize();

	void cleanup(GLFWwindow* window);

private:

	VkInstance instance;

	void createInstance();

};
