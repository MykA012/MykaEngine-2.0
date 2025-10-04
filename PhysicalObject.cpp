#include "PhysicalObject.h"
#include <iostream>
#include "GameObject.h"
//const glm::vec3 GRAVITY = glm::vec3(0.0f, -9.81f * 0.1f, 0.0f);
const glm::vec3 GRAVITY = glm::vec3(0.0f, 0.0f, 0.0f);

PhysicalObject::PhysicalObject() : position(glm::vec3(0.0f)), velocity(glm::vec3(0.0f)), acceleration(glm::vec3(0.0f)), mass(1.0f), transformMatrix(glm::mat4(1.0f)) {}

void PhysicalObject::ApplyForce(const glm::vec3& force)
{
	// F = ma	=>	a = F / m
	acceleration += force / mass;
}

void PhysicalObject::Update(float deltaTime)
{
	// v = v0 + at	=>	v += at
	velocity += (acceleration + GRAVITY) * deltaTime;

	// x = x0 + vt	=>	x += vt
	position += velocity * deltaTime;

	acceleration = glm::vec3(0.0f);

	UpdateTransformMatrix();
}

// SET
void PhysicalObject::SetPosition(const glm::vec3& pos) { position = pos; }

void PhysicalObject::SetVelocity(const glm::vec3& vel) { velocity = vel; }

void PhysicalObject::SetMass(float m) { mass = m; }

// GET
const glm::vec3& PhysicalObject::GetPosition() const { return position; }

const glm::vec3& PhysicalObject::GetVelocity() const { return velocity; }

float PhysicalObject::GetMass() const { return mass; }


void PhysicalObject::UpdateTransformMatrix()
{
	transformMatrix = glm::translate(glm::mat4(1.0f), position);
}