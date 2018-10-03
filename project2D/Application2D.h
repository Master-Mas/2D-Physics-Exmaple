#pragma once
#include <vector>

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "GameObjectTypes.h"
#include "PhysicsScene.h"
#include "Spring.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

	void addObject(GameObject* obj);
	void removeObject(GameObject* obj);
	//void findObject();

private:
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_remove;
	aie::Renderer2D* m_2dRenderer = nullptr;

	PhysicsScene* m_physicsScene = nullptr;

	float m_cameraX, m_cameraY;
	float m_timer;

	RigidBody2D* test1 = nullptr;
	RigidBody2D* test2 = nullptr;

	float ballSpawnWait = 0;

	aie::Font* font;
};