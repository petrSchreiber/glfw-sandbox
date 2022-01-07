
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vulkan/vulkan.h>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


class akaiVulkan
{
public:
    void initialize();

	void cleanup(GLFWwindow* window);

private:

	const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

	VkInstance instance;

	void createInstance();

	bool checkValidationLayerSupport();

};
