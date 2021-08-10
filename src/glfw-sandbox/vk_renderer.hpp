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

	VkInstance instance = nullptr;

	VkDevice device = nullptr;
	VkPhysicalDevice GPU = nullptr;
	VkPhysicalDeviceProperties gpuProperties{};

	uint32_t gpuFamilyIndex = 0;

};