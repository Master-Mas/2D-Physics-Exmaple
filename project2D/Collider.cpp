#include "Collider.h"

Collider::Collider(unsigned int type)
{
	this->colliderTypeID = type;
}


Collider::~Collider()
{
}

bool Collider::getDebug()
{
	return debug;
}

void Collider::setDebug(bool debug)
{
	this->debug = debug;
}

void Collider::setBouncePower(float bounce)
{
	this->bouncePower = bounce;
}

float Collider::getBouncePower()
{
	return bouncePower;
}

void Collider::draw(aie::Renderer2D * renderer)
{
	if (debug)
	{
		drawGizmos();
	}
}

unsigned int Collider::getColliderType()
{
	return colliderTypeID;
}
