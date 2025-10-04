#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
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
	
	// --- ImGui Render ---
	void OnImGuiRender();

private:
	bool ShouldInitializeImgui = true;

	GLFWwindow* window;
	Camera camera;
};