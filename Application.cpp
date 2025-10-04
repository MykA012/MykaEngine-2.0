#include "Application.h"

Application::Application() : camera((int)DEFAULT_WINDOW_WIDTH, (int)DEFAULT_WINDOW_HEIGHT, glm::vec3(0.0f)), window(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow((int)DEFAULT_WINDOW_WIDTH, (int)DEFAULT_WINDOW_HEIGHT, "Simulation", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// TODO: Init Imgui

	glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{

}

void Application::OnUpdate()
{

}
