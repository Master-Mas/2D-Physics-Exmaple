#include "PhysicsScene.h"
#include <algorithm>
#include "GameObject.h"
#include "ColliderTypes.h"

PhysicsScene::PhysicsScene()
{
	
}

PhysicsScene::~PhysicsScene()
{

}

void PhysicsScene::addActor(RigidBody2D * rigidBody)
{
	actors.push_back(rigidBody);
}

void PhysicsScene::removeActor(RigidBody2D * rigidBody)
{
	to_remove.push_back(rigidBody);
}

void PhysicsScene::addFixedUpdateOnly(Component2D * component)
{
	this->fixedUpdateOnly.push_back(component);
}

void PhysicsScene::debugScene(bool debug)
{
}

void PhysicsScene::update(float deltaTime)
{
	static float timer = 0;
	timer += deltaTime;
	int timeStepTotal = 0;

	for (unsigned int i = 0; i < to_remove.size(); ++i)
	{
		actors.erase(std::remove(actors.begin(), actors.end(), to_remove[i]), actors.end());
	}

	while (timer >= timeStep)
	{
		timer -= timeStep;

		for (unsigned int i = 0; i < fixedUpdateOnly.size(); ++i)
		{
			fixedUpdateOnly[i]->fixedUpdate(timeStep, gravity);
		}

		int actorCount = actors.size();
		if (actorCount == 1)
		{
			actors[0]->fixedUpdate(timeStep, gravity);
		}
		else
		{
			for (int outer = 0; outer < actorCount; ++outer)
			{
				RigidBody2D* collider = actors[outer];
				collider->fixedUpdate(timeStep, gravity);

				if (collider == nullptr)
					continue;

				for (int inner = outer + 1; inner < actorCount; ++inner)
				{
					RigidBody2D* collider1 = actors[inner];

					if (collider1 == nullptr)
						continue;

					if (collider->isStatic() && collider1->isStatic())
						continue;

					if (collider->getCollider() == nullptr || collider1->getCollider() == nullptr)
						continue;

					fn collisionFunctionPtr = collisionFunctionArray[(collider->getCollider()->getColliderType() * Collider::COLLIDER_SIZE) + collider1->getCollider()->getColliderType()];
					if (collisionFunctionPtr != nullptr)
					{
						collisionFunctionPtr(collider, collider1);
					}
				}
			}

			timeStepTotal++;
		}
	}
}

void PhysicsScene::setGravity(const glm::vec2 gravity)
{
	this->gravity = gravity;
}

glm::vec2 PhysicsScene::getGravity()
{
	return gravity;
}

void PhysicsScene::setTimeStep(const float timeStep)
{
	this->timeStep = timeStep;
}

float PhysicsScene::getTimeStep() const
{
	return timeStep;
}

void PhysicsScene::checkForCollisions()
{

}

bool PhysicsScene::planeToPlane(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2)
{
	return false;
}

bool PhysicsScene::planeToSphere(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2)
{
	return sphereToPlaneLinker(rigidbody1, rigidbody2);
}

bool PhysicsScene::sphereToPlane(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2)
{
	return sphereToPlaneLinker(rigidbody2, rigidbody1);
}

bool PhysicsScene::sphereToPlaneLinker(RigidBody2D* circleRB, RigidBody2D* planeRB)
{
	ColliderCircle* circle = static_cast<ColliderCircle*>(circleRB->getCollider());
	ColliderPlane* plane = static_cast<ColliderPlane*>(planeRB->getCollider());

	glm::vec2 collisionNormal = plane->getNormal();
	float sphereToPlane = glm::dot(circle->getTransform().getPosition(), plane->getNormal()) - plane->getDistance();
	if (sphereToPlane < 0)
	{
		collisionNormal *= -1;
		sphereToPlane *= -1;
	}

	float intersection = circle->getRadius() - sphereToPlane;
	if (intersection > 0)
	{
		glm::vec2 planeNormal = plane->getNormal();
		glm::vec2 forceVector = -1 * circleRB->getMass() * planeNormal * glm::dot(planeNormal, circleRB->getVelocity());
		circleRB->applyForce((1.0f + plane->getBouncePower()) * forceVector);
		circleRB->getTransform().setPosition(circleRB->getTransform().getPosition() + collisionNormal * intersection * 0.5f);
		return true;
	}

	return false;
}

bool PhysicsScene::sphereToSphere(RigidBody2D * rigidbody1, RigidBody2D * rigidbody2)
{
	ColliderCircle* circle1 = static_cast<ColliderCircle*>(rigidbody1->getCollider());
	ColliderCircle* circle2 = static_cast<ColliderCircle*>(rigidbody2->getCollider());

	glm::vec2 pos1 = circle1->getTransform().getPosition();
	glm::vec2 pos2 = circle2->getTransform().getPosition();

	glm::vec2 delta = pos2 - pos1;
	float distance = glm::length(delta);
	float intersection = circle1->getRadius() + circle2->getRadius() - distance;

	if (intersection > 0)
	{
		glm::vec2 collisionNormal = glm::normalize(delta);
		glm::vec2 relativeVelocity = rigidbody1->getVelocity() - rigidbody2->getVelocity();
		glm::vec2 collisionVector = collisionNormal * glm::dot(relativeVelocity, collisionNormal);
		glm::vec2 forceVector = collisionVector / (1.0f / rigidbody1->getMass() + 1.0f / rigidbody2->getMass());
		
		rigidbody1->applyForceToActor(rigidbody2, forceVector * (1.0f + circle1->getBouncePower()));

		glm::vec2 separationVector = collisionNormal * intersection * 0.5f;

		if (rigidbody1->isStatic())
			rigidbody2->getTransform().setPosition(pos1 - (separationVector * 2));
		if (rigidbody2->isStatic())
			rigidbody1->getTransform().setPosition(pos2 + (separationVector * 2));
		if (!rigidbody2->isStatic() && !rigidbody1->isStatic())
		{
			rigidbody1->getTransform().setPosition(pos1 - separationVector);
			rigidbody2->getTransform().setPosition(pos2 + separationVector);
		}

		return true;
	}

	return false;
}
