#pragma once
#include "Collider.h"
class ColliderPlane :
	public Collider
{
public:
	ColliderPlane();
	~ColliderPlane();

	glm::vec2 getNormal();
	void setNormal(glm::vec2* normal);

	float getDistance();
	void setDistance(float distance);

private:
	glm::vec2* normal;
	float distance;

	// Inherited via Collider
	virtual void drawGizmos() override;
};

