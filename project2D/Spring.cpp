#include "Spring.h"

Spring::Spring(RigidBody2D * join1, RigidBody2D * join2, float springConstant, float damping)
{
	this->join1 = join1;
	this->join2 = join2;

	this->springConstant = springConstant;
	this->damping = damping;
	this->restDistance = glm::length(join1->getTransform().getPosition() - join2->getTransform().getPosition());
}

Spring::~Spring()
{
}

void Spring::fixedUpdate(float fixedTimeStep, glm::vec2 gravity)
{
	float force = -springConstant * (glm::distance(join1->getTransform().getPosition(), join2->getTransform().getPosition()) - restDistance) - damping * glm::length(join1->getVelocity() - join2->getVelocity());

	join2->applyForce(glm::normalize(join2->getTransform().getPosition() - join1->getTransform().getPosition()) * force * fixedTimeStep);
}

void Spring::draw(aie::Renderer2D * renderer)
{
	renderer->setRenderColour(0, 0, 1);
	glm::vec2 pos1 = join1->getTransform().getPosition();
	glm::vec2 pos2 = join2->getTransform().getPosition();
	renderer->drawLine(pos1.x, pos1.y, pos2.x, pos2.y);
}
