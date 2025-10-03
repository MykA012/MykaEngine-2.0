#include "Camera.h"

Camera::Camera(int width, int height, const glm::vec3& position) : m_Width(width), m_Height(height), m_Position(position)
{
	UpdateMatrices(45.0f, 0.1f, 100.f);
}

void Camera::UpdateMatrices(float fov, float zNear, float zFar)
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);

	m_ProjectionMatrix = glm::perspective(glm::radians(fov), (float)m_Width / (float)m_Height, zNear, zFar);
}

const glm::mat4& Camera::GetViewMatrix() const { return m_ViewMatrix; }

const glm::mat4& Camera::GetProjectionMatrix() const { return m_ProjectionMatrix; }

void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	// Keyboard
	float velocity = m_Speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += velocity * m_Front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += velocity * -glm::normalize(glm::cross(m_Front, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += velocity * -m_Front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += velocity * glm::normalize(glm::cross(m_Front, m_Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += velocity * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += velocity * -m_Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Speed = 1.0f * 3.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Speed = 1.0f;
	}

	// Mouse
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// 1. Активируем режим захвата курсора
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (m_FirstClick)
		{
			// 2. При первом клике инициализируем m_LastX и m_LastY
			m_LastX = mouseX;
			m_LastY = mouseY;
			m_FirstClick = false;
		}

		// 3. Вычисляем смещение (разницу с предыдущим кадром)
		float xoffset = (float)mouseX - (float)m_LastX;
		float yoffset = (float)m_LastY - (float)mouseY; // Инверсия Y для интуитивного движения

		// 4. Обновляем m_LastX и m_LastY для следующего кадра
		m_LastX = mouseX;
		m_LastY = mouseY;

		// 5. Применяем чувствительность
		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		// 6. Обновляем углы Yaw и Pitch
		m_Yaw += xoffset;
		m_Pitch += yoffset;

		// 7. Ограничиваем Pitch (тангаж)
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		// 8. Пересчитываем вектор m_Front
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Возвращаем курсор в обычный режим
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_FirstClick = true; // Сбрасываем флаг для следующей инициализации
	}
}