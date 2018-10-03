#pragma once
#include "GameObject.h"
class ShapeCircle :
	public GameObject
{
public:
	ShapeCircle();
	ShapeCircle(float radius);
	~ShapeCircle();

	void update(float deltaTime) override;
	void draw(aie::Renderer2D& renderer) override;

	void setRadius(float radius);
	float getRadius();
	float* getRadiusPointer();

private:
	float radius = 1;
};