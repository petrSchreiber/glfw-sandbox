#pragma once


#include "vulkan/vulkan.h"
#include <vector>
#include <optional>


// Adding more functions than they are present in the vulkan tutorial as Device Query needs an instance.
// Therefore need a setter for Instance and probably a few more things along the way.
// When enough experience is gained might just use inheritance but lets-
// -keep it this way till we figure vulkan out better ;) 

class akaiPhysicalDevice
{
public:

	// Original function to pick a physical device per vulkan tutorial.
	void pickPhysicalDevice();

	// Testing/Placeholder if needed
	VkPhysicalDevice returnPhysicalDevice();

	// Returns if device is suitable
	bool isDeviceSuitable(VkPhysicalDevice device);

	bool isDeviceSuitableIndices(VkPhysicalDevice device);

	// Setter for Vulkan created instance
	void setInstance(VkInstance instance);

	void createLogicalDevice();

	// Dark Wizardry
	//struct QueueFamilyIndices {};
	//QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	// Dark Wizardry CopyPasta from the Vulkan Tutorial website...
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;

		bool isComplete() {
			return graphicsFamily.has_value();
		}
	};

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}

private:

	

	

	std::vector<VkPhysicalDevice> devices{};
	

	// Setting instance to be null, will need to initiate it first and get it here for device queue
	VkInstance instance = VK_NULL_HANDLE;

	// This is where the device will be stored
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;

	// Device count, if more GPUs that support vulkan are found.
	uint32_t deviceCount = 0;

	// Device properties and features, useful when using the debugger...
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;

	

	

};

