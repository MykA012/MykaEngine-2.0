#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture) : vertices(vertices), indices(indices), texture(texture)
{
	VAO.Bind();

	VBO.BufferData(vertices);

	IBO.Bind();
	IBO.BufferData(indices);

	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VBO.VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	IBO.Unbind();
	VBO.Unbind();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const Texture& texture) : vertices(vertices), texture(texture)
{
	VAO.Bind();

	VBO.BufferData(vertices);

	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VBO.VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	IBO.Unbind();
	VBO.Unbind();
}

void Mesh::Draw(Shader& shader, glm::mat4& model, Camera& camera)
{
	shader.CompileShaders();
	shader.Use();

	shader.SetMatrix4("model", model);
	shader.SetMatrix4("view", camera.GetViewMatrix());
	shader.SetMatrix4("projection", camera.GetProjectionMatrix());
	shader.SetInteger("tex0", 0);

	texture.Bind();

	VAO.Bind();

	if (indices.empty())
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	VAO.Unbind();

}