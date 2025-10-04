#include "Window.h"

Window::Window(int width, int height, const std::string& title) : window(nullptr)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetWindow()
{
	return window;
}