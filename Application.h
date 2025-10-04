#pragma once

//#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"
#include "Defaults.h"

class Application
{
public:
	Application();
	~Application();

	void OnUpdate();

private:
	GLFWwindow* window;

	Camera camera;
};