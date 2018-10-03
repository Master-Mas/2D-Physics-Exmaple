#pragma once
#include "GameObject.h"
class ShapePlane :
	public GameObject
{
public:
	ShapePlane(glm::vec2 normal, float distanceToOrigin);
	~ShapePlane();

	void update(float deltaTime) override;
	void draw(aie::Renderer2D& renderer) override;

	glm::vec2* getNormal();
	float getDistance();

private:
	glm::vec2 normal;
	float distanceToOrigin = 0;
};

