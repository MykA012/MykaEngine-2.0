#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "GameObject.h"

int width = 1920;
int height = 1080;
int transparentKey = GLFW_KEY_T;

std::string CURRENT_DIR = "C:/Users/Vova/source/repos/MykaEngine 2.0";

/*
TODO:

Заменить наследование на shared_ptr + unique_ptr в классe GameObject

Улучшить структуру:
	+ Внедрить ImGui	DONE

	- Создать класс Renderable в нем shared_ptr<Mesh>, Texture, modelMatrix	+ убрать из Mesh modelMatrix;

	- Переписать GameObject под shared_ptr Вместо множественного наследования

	- Создать класс Simulation (куб с видимыми границами которые будут границами симуляции)

	- Доделать класс Application
*/

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	// Rotation vars
	float rotation = 0.0f;
	float deltaTime = 0.0f;
	float prevTime = 0.0f;


	// imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// imgui init

	glEnable(GL_DEPTH_TEST);


	std::vector<Vertex> vertices = {
		// front
		Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)},

		// back
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},

		// right
		 Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},

		 Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},

		 // left
		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},

		 // top
		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)},

		 // bottom
		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 1.0f)}
	};


	Texture brick((CURRENT_DIR + "/brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture grass_block((CURRENT_DIR + "/grass_block.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Shader shader(CURRENT_DIR + "/floorVert.glsl", CURRENT_DIR + "/floorFrag.glsl");

	GameObject obj(vertices, brick);
	//obj.SetVelocity(glm::vec3(1.0f, 2.0f, 0.0f));

	// Camera
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 5.0f));

	while (!glfwWindowShouldClose(window))
	{
		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// imgui

		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// make transparent
		if (glfwGetKey(window, transparentKey) == GLFW_PRESS)
		{
			glEnable(GL_POLYGON_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (glfwGetKey(window, transparentKey) == GLFW_RELEASE)
		{
			glDisable(GL_POLYGON_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0 / 60)
		{
			rotation += 0.5f;
			deltaTime = crntTime - prevTime;
			prevTime = crntTime;
		}

		camera.Inputs(window, deltaTime);
		camera.UpdateMatrices(45.0f, 0.1f, 100.0f);


		obj.Update(deltaTime);
		obj.Render(shader, camera);


		// imgui
		if (ImGui::Begin("Main"))
		{
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}