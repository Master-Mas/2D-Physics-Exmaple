#pragma once
#include "Transform2D.h"
#include <Renderer2D.h>
#include <iostream>
class Component2D
{
public:
	Component2D();
	~Component2D();

	virtual void update(float deltaTime);
	virtual void fixedUpdate(float timeStep, glm::vec2 gravity);

	virtual void draw(aie::Renderer2D* renderer);

	void setTransform(Transform2D* transform);
	Transform2D& getTransform();
protected:
	Transform2D* transform = nullptr;
};

