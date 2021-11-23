#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "akaiWindow.cpp"

void akaiWindow::akaiWindowInit()
{	
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	std::cout << "DEBUG: Vulkan Window created successfully" << std::endl;
}

void akaiWindow::akaiWindowMainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

GLFWwindow* akaiWindow::akaiGetWindow() {

	std::cout << "DEBUG: Vulkan Window returned successfully" << std::endl;
	return window;
}

bool akaiWindow::akaiWindowOpen() {
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		return true;
	}
	std::cout << "DEBUG: Vulkan Window closed" << std::endl;
	return !glfwWindowShouldClose(window);
	
}

void akaiWindow::akaiWindowCleanup() {
	glfwDestroyWindow(window);

	glfwTerminate();
	std::cout << "DEBUG: Vulkan Window destroyed successfully" << std::endl;
}