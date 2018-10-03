#include "ColliderCircle.h"



ColliderCircle::ColliderCircle() : Collider(Collider::COLLIDER_CIRCLE)
{
	this->bouncePower = 0.5f;
}


ColliderCircle::~ColliderCircle()
{
}

void ColliderCircle::setRadius(float * radius)
{
	this->radius = radius;
}

float ColliderCircle::getRadius()
{
	return *radius;
}

void ColliderCircle::drawGizmos()
{
	//aie::Gizmos::draw2D(glm::ortho<float>)
}
