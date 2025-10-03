#include <filesystem>

namespace fs = std::filesystem;

#include "Object.h"

int width = 800;
int height = 600;
int transparentKey = GLFW_KEY_T;


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

	glEnable(GL_DEPTH_TEST);



	std::vector<Vertex> vert = {
		Vertex{glm::vec3(-0.5f, 0.0f, 0.5f),  glm::vec3(1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),  glm::vec3(1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.0f, 0.5f),	  glm::vec3(1.0f), glm::vec2(1.0f, 0.0f)},
	};
	
	std::vector<GLuint> ind = {
		0, 1, 2,
		2, 3, 0
	};


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
		Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
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
		 Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)},

		 // bottom
		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 1.0f)}
	};


	Texture brick((fs::current_path().string() + "/brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture grass_block((fs::current_path().string() + "/grass_block.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Shader shader(fs::current_path().string() + "/floorVert.glsl", fs::current_path().string() + "/floorFrag.glsl");

	Object obj(vertices, brick);

	// Camera
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 5.0f));

	while (!glfwWindowShouldClose(window))
	{
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

		obj.Update(shader, camera, deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}