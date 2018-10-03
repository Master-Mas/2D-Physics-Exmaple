#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ColliderTypes.h"
#include <algorithm>
#include <Gizmos.h>


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	m_2dRenderer = new aie::Renderer2D();

	m_physicsScene = new PhysicsScene(); 
	m_physicsScene->setGravity(glm::vec2(0, -980.0f));
	m_physicsScene->setTimeStep(0.005f);

	font = new aie::Font("./font/consolas.ttf", 8);

	//Shape Setup
	ShapePlane* plane = new ShapePlane(glm::vec2(-1.5f, 1.5f), -400);

	//Collider
	ColliderPlane* pCollider = new ColliderPlane();
	pCollider->setNormal(plane->getNormal());
	pCollider->setDistance(plane->getDistance());
	plane->addComponent(pCollider);

	//Rigidbody
	RigidBody2D* rigidBody2 = new RigidBody2D(pCollider);
	rigidBody2->setGravity(false);
	//rigidBody2->setDrag(0.0f);
	rigidBody2->setStatic(true);
	plane->addComponent(rigidBody2);

	//Add to scene
	m_physicsScene->addActor(rigidBody2);
	addObject(plane);

	//Shape Setup
	ShapePlane* plane1 = new ShapePlane(glm::vec2(1.5, 1.5f), 400);

	//Collider
	ColliderPlane* pCollider1 = new ColliderPlane();
	pCollider1->setNormal(plane1->getNormal());
	pCollider1->setDistance(plane1->getDistance());
	plane1->addComponent(pCollider1);

	RigidBody2D* rigidBody3 = new RigidBody2D(pCollider1);
	//rigidBody3->setDrag(1.0f);
	rigidBody3->setGravity(false);
	rigidBody3->setStatic(true);
	plane1->addComponent(rigidBody3);

	//Add to scene
	m_physicsScene->addActor(rigidBody3);
	addObject(plane1);

	ShapeCircle* circle = new ShapeCircle(30.0f);
	circle->getTransform().setPosition(glm::vec2(200, 300));
	ColliderCircle* cCollider = new ColliderCircle();
	cCollider->setRadius(circle->getRadiusPointer());
	circle->addComponent(cCollider);
	RigidBody2D* rigidBody = new RigidBody2D(nullptr);
	rigidBody->setGravity(false);
	rigidBody->setStatic(true);
	rigidBody->setMass(1.0f);
	circle->addComponent(rigidBody);

	ShapeCircle* circle1 = new ShapeCircle(30.0f);
	circle1->getTransform().setPosition(glm::vec2(300, 400));
	cCollider = new ColliderCircle();
	cCollider->setRadius(circle1->getRadiusPointer());
	circle1->addComponent(cCollider);
	RigidBody2D* rigidBody1 = new RigidBody2D(cCollider);
	rigidBody1->setMass(15.0f);
	circle1->addComponent(rigidBody1);

	Spring* spring = new Spring(rigidBody, rigidBody1, 100.0f, 0.000001f);
	circle->addComponent(spring);

	addObject(circle);
	addObject(circle1);

	m_physicsScene->addActor(rigidBody);
	m_physicsScene->addActor(rigidBody1);
	m_physicsScene->addFixedUpdateOnly(spring);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		delete m_gameObjects[i];
	}

	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) /*&& ballSpawnWait > 0.01f*/)
	{
		//Shape Setup
		ShapeCircle* circle = new ShapeCircle(rand() % 50);
		circle->getTransform().setPosition(glm::vec2(input->getMouseX(), input->getMouseY()));
		circle->setColor(glm::vec4((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1));

		//Collision Setup
		ColliderCircle* cCollider = new ColliderCircle();
		cCollider->setRadius(circle->getRadiusPointer());
		circle->addComponent(cCollider);

		//RigidBody Setup
		RigidBody2D* rigidBody = new RigidBody2D(cCollider);
		rigidBody->setMass(circle->getRadius() / 2);
		//rigidBody->setDrag(0.0f);
		circle->addComponent(rigidBody);

		//Add to Scene
		m_physicsScene->addActor(rigidBody);
		addObject(circle);

		ballSpawnWait = 0;
	}
	else
	{
		//ballSpawnWait += deltaTime;
	}

	m_physicsScene->update(deltaTime);

	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->internalUpdate(deltaTime);
		if (m_gameObjects[i]->isDestoryed())
		{
			this->m_remove.push_back(m_gameObjects[i]);
		}
	}

	for (unsigned int i = 0; i < m_remove.size(); ++i)
	{
		m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), m_remove[i]), m_gameObjects.end());
		m_physicsScene->removeActor((RigidBody2D*)m_remove[i]->unSafeGetComponentsList().at(1));
		delete m_remove[i];
	}

	m_remove.clear();

	std::cout << m_gameObjects.size() << "\n";
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRatio = 16 / 9.f; 
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	for (unsigned int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->externalDraw(*m_2dRenderer);
	}

	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::addObject(GameObject * obj)
{
	obj->setFont(font);
	m_gameObjects.push_back(obj);
}

void Application2D::removeObject(GameObject * obj)
{
	m_remove.push_back(obj);
}
