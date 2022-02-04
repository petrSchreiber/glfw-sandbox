#include "akaiPhysicalDevice.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>

void akaiPhysicalDevice::pickPhysicalDevice() {

    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device) and isDeviceSuitableIndices(device)) {
            std::cout << "GPU Used: " << deviceProperties.deviceName << std::endl;
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
	
};

VkPhysicalDevice akaiPhysicalDevice::returnPhysicalDevice() {

	return physicalDevice;

}

bool akaiPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {

    // Saved these in the object, uses a little memory but helps a lot with the debugging...
    //VkPhysicalDeviceProperties deviceProperties;
    //VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
        deviceFeatures.geometryShader;

}

bool akaiPhysicalDevice::isDeviceSuitableIndices(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.isComplete();
}

void akaiPhysicalDevice::setInstance(VkInstance instanc) {

    instance = instanc;
}

//The code below is dark wizardry beyond my understanding...
//
/* 
struct akaiPhysicalDevice::QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

akaiPhysicalDevice::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    akaiPhysicalDevice::QueueFamilyIndices indices;

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
} */