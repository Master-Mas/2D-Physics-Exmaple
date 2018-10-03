#include "ColliderPlane.h"



ColliderPlane::ColliderPlane() : Collider(Collider::COLLIDER_PLANE)
{
	bouncePower = 0.5f;
}


ColliderPlane::~ColliderPlane()
{
}

glm::vec2 ColliderPlane::getNormal()
{
	return *normal;
}

void ColliderPlane::setNormal(glm::vec2 * normal)
{
	this->normal = normal;
}

float ColliderPlane::getDistance()
{
	return distance;
}

void ColliderPlane::setDistance(float distance)
{
	this->distance = distance;
}

void ColliderPlane::drawGizmos()
{
}
