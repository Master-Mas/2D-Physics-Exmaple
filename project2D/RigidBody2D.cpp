#include "RigidBody2D.h"

RigidBody2D::RigidBody2D(Collider* collider)
{
	this->collider = collider;
}

RigidBody2D::~RigidBody2D()
{
}

void RigidBody2D::update(float deltaTime)
{

}

void RigidBody2D::fixedUpdate(float timeStep, glm::vec2 gravity)
{
	if (!staticRB)
	{
		if (this->gravity)
			applyForce(gravity * mass * timeStep);

		velocity *= drag;

		transform->translate(velocity * timeStep);
	}
}

void RigidBody2D::applyForce(glm::vec2 force)
{
	velocity += force / mass;
}

void RigidBody2D::applyForceToActor(RigidBody2D* actor, glm::vec2 force)
{
	applyForce(-force);
	actor->applyForce(force);
}

void RigidBody2D::setMass(float mass)
{
	this->mass = mass;
}

float RigidBody2D::getMass()
{
	return mass;
}

void RigidBody2D::setGravity(bool gravity)
{
	this->gravity = gravity;
}

bool RigidBody2D::useGravity()
{
	return gravity;
}

void RigidBody2D::setStatic(bool staticRB)
{
	this->staticRB = staticRB;
	if (staticRB)
		mass = FLT_MAX;
}

bool RigidBody2D::isStatic()
{
	return staticRB;
}

glm::vec2 RigidBody2D::getVelocity()
{
	return velocity;
}

void RigidBody2D::zeroOutVelocity()
{
	velocity = glm::vec2();
}

void RigidBody2D::setDrag(float drag)
{
	this->drag = 1.0f - drag;
}

float RigidBody2D::getDrag()
{
	return drag;
}

float * RigidBody2D::getDragPointer()
{
	return &drag;
}

void RigidBody2D::setVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
}

Collider * RigidBody2D::getCollider()
{
	return collider;
}
