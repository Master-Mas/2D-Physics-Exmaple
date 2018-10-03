#include "ShapeJoint.h"

ShapeJoint::ShapeJoint(RigidBody2D * join1, RigidBody2D * join2, float springConstant, float damping)
{

	this->join1 = join1;
	this->join2 = join2;

	this->springConstant = springConstant;
	this->damping = damping;
}

ShapeJoint::~ShapeJoint()
{

}

void ShapeJoint::update(float deltaTime)
{

}

void ShapeJoint::draw(aie::Renderer2D & renderer)
{
	glm::vec2 pos1 = join1->getTransform().getPosition();
	glm::vec2 pos2 = join2->getTransform().getPosition();
	renderer.drawLine(pos1.x, pos1.y, pos2.x, pos2.y);
}
