#pragma once

#include "Mesh.h"
#include "PhysicalObject.h"

class GameObject : public Mesh, public PhysicalObject
{
public:
	GameObject(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture);
	GameObject(const std::vector<Vertex>& vertices, const Texture& texture);

	void Update(float deltaTime);
	void Render(Shader& shader, Camera& camera);
};