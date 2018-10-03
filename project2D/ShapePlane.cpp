#include "ShapePlane.h"



ShapePlane::ShapePlane(glm::vec2 normal, float distanceToOrigin)
{
	this->normal = glm::normalize(normal);
	this->distanceToOrigin = distanceToOrigin;
}


ShapePlane::~ShapePlane()
{
}

void ShapePlane::update(float deltaTime)
{
}

void ShapePlane::draw(aie::Renderer2D & renderer)
{
	float lineSegmentLength = 5000; 
	glm::vec2 centerPoint = normal * distanceToOrigin; 
	// easy to rotate normal through 90 degrees around z 
	glm::vec2 parallel(normal.y, -normal.x);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength); 
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	renderer.drawLine(start.x, start.y, end.x, end.y);
	//renderer.drawCircle(centerPoint.x + 3, centerPoint.y + 3, 5);
}

glm::vec2 * ShapePlane::getNormal()
{
	return &normal;
}

float ShapePlane::getDistance()
{
	return distanceToOrigin;
}
