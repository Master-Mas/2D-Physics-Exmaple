#include "Component2D.h"



Component2D::Component2D()
{
}


Component2D::~Component2D()
{
}

void Component2D::update(float deltaTime) { }

void Component2D::fixedUpdate(float timeStep, glm::vec2 gravity)
{

}

void Component2D::draw(aie::Renderer2D* renderer)
{
}

void Component2D::setTransform(Transform2D * transform)
{
	this->transform = transform;
}

Transform2D & Component2D::getTransform()
{
	return *transform;
}
