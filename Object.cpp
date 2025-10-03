#include "Object.h"

Object::Object(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture) : Mesh(vertices, indices, texture), PhysicalObject() {}

Object::Object(const std::vector<Vertex>& vertices, const Texture& texture) : Mesh(vertices, texture), PhysicalObject() {}

void Object::Update(Shader& shader, Camera& camera, float deltaTime)
{
	PhysicalObject::OnUpdate(deltaTime);

	Mesh::Draw(shader, transformMatrix, camera);
}
