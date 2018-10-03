#pragma once
#include "GameObject.h"
class ShapeJoint :
	public GameObject
{
public:
	ShapeJoint(RigidBody2D* join1, RigidBody2D* join2, float springConstant, float damping);
	~ShapeJoint();

	void update(float deltaTime) override;
	void draw(aie::Renderer2D& renderer) override;

private:
	
};

