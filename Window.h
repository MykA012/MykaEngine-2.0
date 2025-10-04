#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void PollEvents();
	void SwapBuffers();
	bool ShouldClose();

public:
	GLFWwindow* GetWindow();

private:
	GLFWwindow* window;
};