#pragma once


#include "vulkan/vulkan.h"

class Renderer {

private:

public:

	Renderer();
	~Renderer();

private:

	void initInstance();
	void deInitInstance();

	void initDevice();
	void deInitDevice();

	VkInstance instance = VK_NULL_HANDLE;

	VkDevice device = VK_NULL_HANDLE;
	VkPhysicalDevice GPU = VK_NULL_HANDLE;
	VkPhysicalDeviceProperties gpuProperties{};

	uint32_t gpuFamilyIndex = 0;

};