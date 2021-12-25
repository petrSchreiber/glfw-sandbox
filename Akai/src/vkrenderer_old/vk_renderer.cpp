
#include "vk_renderer.hpp"
#include <cstdlib>
#include <assert.h>
#include "vulkan/vulkan.h"
#include <vector>

Renderer::Renderer() {
	initInstance();
	initDevice();
}

Renderer::~Renderer() {
	deInitInstance();
	deInitDevice();
}

void Renderer::initInstance()
{	
	/*This is the part related to the application/engine info*/
	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	/*Tells application/driver which Vulkan version this application uses*/
	applicationInfo.apiVersion				= VK_API_VERSION_1_2;
	applicationInfo.applicationVersion		= VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pApplicationName		= "AKAI Engine";

	/*Here we create  the parameters that vkCreateInstance uses and their parameters*/
	VkInstanceCreateInfo instanceCreateInfo{};
	
	/*sType is always required for all Vulkan structures or types and its mostly the same for each type*/
	/*Its usually VK_STRUCTURE_TYPE_ + name of the structure*/
	instanceCreateInfo.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo		= &applicationInfo;

	auto err = vkCreateInstance(&instanceCreateInfo, VK_NULL_HANDLE, &instance);
	if (VK_SUCCESS != err)
	{
		assert( 0 && "Vulkan Error: Create instance failed");
		std::exit(-1);

	}


}

void Renderer::deInitInstance()
{
	/*Function to destroy the instance once its not needed or program terminated*/
	vkDestroyInstance(instance, VK_NULL_HANDLE);
	
	/*This should be a failsafe that the instance is destroyed (just in case)
	May not be needed but keeping it for now - will experiment*/
	instance = nullptr;



}

void Renderer::initDevice()
{	


	/*Fun Part, getting the physical device here*/
	uint32_t gpuCount = 0;
	vkEnumeratePhysicalDevices(instance, &gpuCount, VK_NULL_HANDLE);
	std::vector<VkPhysicalDevice> gpuList(gpuCount);
	/*This populates the lsit of GPUs, first one is probably the main one
	There are probably better ways*/
	vkEnumeratePhysicalDevices(instance, &gpuCount, gpuList.data());
	GPU = gpuList[0];

	/*Get device properties like the name of the GPU
	This is important to identify the device
	First param is the GPU and the last one is return value - it fills the GPU properties*/
	vkGetPhysicalDeviceProperties(GPU, &gpuProperties);


	/*How many families in this GPU*/
	uint32_t familiyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(GPU, &familiyCount, VK_NULL_HANDLE);
	std::vector<VkQueueFamilyProperties> familyPropertyList{ familiyCount };
	vkGetPhysicalDeviceQueueFamilyProperties(GPU, &familiyCount, familyPropertyList.data());

	bool gpuFound = false;
	for (uint32_t i = 0; i < familiyCount; i++)
	{
		if (familyPropertyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			gpuFound = true;
			gpuFamilyIndex = i;
		}
	}
	
	if (!gpuFound)
	{
		assert(0 && "Vulkan Error: Queue Family supporting graphics not found");
		std::exit(-1);
	}


	

	float queuePrioritiesList[]{ 1.0f };

	VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
	deviceQueueCreateInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex		= gpuFamilyIndex;
	deviceQueueCreateInfo.queueCount			= 1;
	deviceQueueCreateInfo.pQueuePriorities		= queuePrioritiesList;
	
	
	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType						= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount		= 1;
	deviceCreateInfo.pQueueCreateInfos			= &deviceQueueCreateInfo;

	auto error = vkCreateDevice(GPU, &deviceCreateInfo, VK_NULL_HANDLE, &device);
	if (VK_SUCCESS != error) {
		assert(0 && "Vulkan Error: Device creation failed");
		std::exit(-1);
	}





}

void Renderer::deInitDevice()
{

	vkDestroyDevice(device, VK_NULL_HANDLE);
	device = VK_NULL_HANDLE;

}
