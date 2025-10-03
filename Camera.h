#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


class Camera
{
public:
	Camera(int width, int height, const glm::vec3& position);
	void UpdateMatrices(float fov, float zNear, float zFar);

	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;

	void Inputs(GLFWwindow* window, float deltaTime);

private:
	glm::vec3 m_Position;
	glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

	int m_Width;
	int m_Height;

	float m_Speed = 1.0f;

	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	bool m_FirstClick = true;
	float m_MouseSensitivity = 0.1f;

	double m_LastX;
	double m_LastY;
};