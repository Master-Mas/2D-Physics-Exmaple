#pragma once
#include "Component2D.h"
#include "Collider.h"
class RigidBody2D :
	public Component2D
{
public:
	RigidBody2D(Collider* collider);
	~RigidBody2D();

	void update(float deltaTime) override;
	void fixedUpdate(float timeStep, glm::vec2 gravity) override;

	void applyForce(glm::vec2 force);
	void applyForceToActor(RigidBody2D * actor, glm::vec2 force);

	void setMass(float mass);
	float getMass();

	void setGravity(bool gravity);
	bool useGravity();

	void setStatic(bool isStatic);
	bool isStatic();

	glm::vec2 getVelocity();
	void setVelocity(glm::vec2 velocity);
	void zeroOutVelocity();

	void setDrag(float drag);
	float getDrag();
	float* getDragPointer();

	Collider* getCollider();
private:
	float mass = 0;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	Collider* collider = nullptr;
	bool gravity = true;
	bool staticRB = false;
	float drag = 1.0f;
};

