#pragma once
#include "Component2D.h"
#include "Transform2D.h"
#include "Renderer2D.h"
#include <vector>
#include <Gizmos.h>
#include <Font.h>
#include "RigidBody2D.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void externalDraw(aie::Renderer2D& renderer);
	virtual void draw(aie::Renderer2D& renderer);
	virtual void internalUpdate(float deltaTime);

	Transform2D& getTransform();

	void setColor(glm::vec4 color);
	glm::vec4 getColor();

	void addComponent(Component2D* component);
	void removeComponent(Component2D* component);

	void destory();
	bool isDestoryed();

	void setFont(aie::Font* font);

	template<Component2D* T> Component2D* getComponent();

	std::vector<Component2D*> unSafeGetComponentsList();

protected:
	Transform2D transform;
	glm::vec4 color = glm::vec4(1, 1, 1, 1);

	std::vector<Component2D*> m_components;
	std::vector<Component2D*> to_remove;

	aie::Font* font = nullptr;

	virtual void update(float deltaTime);

private:
	bool flagForDestory = false;

};

template<Component2D* T>
Component2D * GameObject::getComponent()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		if (dynamic_cast<T>(m_components[i]) != 0)
		{
			return m_components[i];
		}
	}

	return nullptr;
}
