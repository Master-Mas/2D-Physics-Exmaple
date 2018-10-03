#pragma once
#include "Collider.h"
class ColliderCircle :
	public Collider
{
public:
	ColliderCircle();
	~ColliderCircle();

	void setRadius(float* radius);
	float getRadius();

	void drawGizmos() override;

private:
	float* radius = nullptr;
};

