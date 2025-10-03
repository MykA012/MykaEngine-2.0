#pragma once

#include "Mesh.h"
#include "PhysicalObject.h"

class Object : public Mesh, public PhysicalObject
{
public:
	Object(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture);
	Object(const std::vector<Vertex>& vertices, const Texture& texture);

	void Update(Shader& shader, Camera& camera, float deltaTime);
};