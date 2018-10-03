#pragma once
#include "RigidBody2D.h"
#include <vector>

typedef bool(*fn)(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2);

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(RigidBody2D* rigidBody);
	void removeActor(RigidBody2D* rigidBody);
	void addFixedUpdateOnly(Component2D* component);
	void debugScene(bool debug);
	void update(float deltaTime);

	void setGravity(const glm::vec2 gravity);
	glm::vec2 getGravity();

	void setTimeStep(const float timeStep);
	float getTimeStep() const;

	void checkForCollisions();

	static bool planeToPlane(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2);
	static bool planeToSphere(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2);
	static bool sphereToPlane(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2);
	static bool sphereToPlaneLinker(RigidBody2D * circle, RigidBody2D * plane);
	static bool sphereToSphere(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2);

protected:
	glm::vec2 gravity;
	float timeStep;
	float currentTime;
	std::vector<RigidBody2D*> actors;
	std::vector<RigidBody2D*> to_remove;
	std::vector<Component2D*> fixedUpdateOnly;

private:
	fn collisionFunctionArray[4] =
	{	PhysicsScene::sphereToSphere, PhysicsScene::planeToSphere,
		PhysicsScene::sphereToPlane, PhysicsScene::planeToPlane
	};
};

