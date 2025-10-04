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

	if (ShouldInitializeImgui)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{
	if (ShouldInitializeImgui)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::OnUpdate()
{
	if (ShouldInitializeImgui)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// GameObjects Rendering

	if (ShouldInitializeImgui)
	{
		OnImGuiRender();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

void Application::OnImGuiRender()
{
	if (ImGui::Begin("Main"))
	{
		ImGui::End();
	}
}
