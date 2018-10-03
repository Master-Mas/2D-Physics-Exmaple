#include "ShapeCircle.h"

ShapeCircle::ShapeCircle()
{
}

ShapeCircle::ShapeCircle(float radius)
{
	this->radius = radius;
}


ShapeCircle::~ShapeCircle()
{
}

void ShapeCircle::update(float deltaTime)
{
	if (this->getTransform().getPosition().y - (getRadius() / 2) < 0)
	{
		destory();
	}
}

void ShapeCircle::draw(aie::Renderer2D & renderer)
{
	renderer.setRenderColour(color.r, color.b, color.g, color.a);
	glm::vec2 pos = transform.getPosition();
	renderer.drawCircle(pos.x, pos.y, radius);

	//std::string velocity = "V: ";
	//

	//velocity.append(getComponent<RigidBody2D*>())
	//renderer.drawText(font, , transform.getPosition().x, transform.getPosition().y + radius + 3);
}

void ShapeCircle::setRadius(float radius)
{
	this->radius = radius;
}

float ShapeCircle::getRadius()
{
	return radius;
}

float * ShapeCircle::getRadiusPointer()
{
	return &radius;
}
