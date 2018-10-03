#pragma once
#include "Component2D.h"
#include "RigidBody2D.h"
class Spring :
	public Component2D
{
public:
	Spring(RigidBody2D* join1, RigidBody2D* join2, float springConstant, float damping);
	~Spring();

	void draw(aie::Renderer2D* renderer) override;
	void fixedUpdate(float fixedTimeStep, glm::vec2 gravity);

private:
	RigidBody2D* join1 = nullptr;
	RigidBody2D* join2 = nullptr;

	float restDistance = 0;
	float springConstant = 0;
	float damping = 0;
};

