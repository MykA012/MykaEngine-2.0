#include "GameObject.h"

GameObject::GameObject(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture) : Mesh(vertices, indices, texture), PhysicalObject() {}

GameObject::GameObject(const std::vector<Vertex>& vertices, const Texture& texture) : Mesh(vertices, texture), PhysicalObject() {}

void GameObject::Update(float deltaTime)
{
	PhysicalObject::Update(deltaTime);
}

void GameObject::Render(Shader& shader, Camera& camera)
{
	Mesh::Draw(shader, transformMatrix, camera);
}