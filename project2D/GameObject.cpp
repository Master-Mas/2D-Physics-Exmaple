#include "GameObject.h"
#include <iostream>
#include <algorithm>


GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	for (int i = 0; i < m_components.size(); ++i)
	{
		delete m_components[i];
	}
}

void GameObject::externalDraw(aie::Renderer2D & renderer)
{
	draw(renderer);

	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		m_components[i]->draw(&renderer);
	}
}

void GameObject::draw(aie::Renderer2D & renderer)
{
	
}

void GameObject::internalUpdate(float deltaTime)
{
	update(deltaTime);

	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		m_components[i]->update(deltaTime);
	}

	for (unsigned int i = 0; i < to_remove.size(); ++i)
	{
		m_components.erase(std::remove(m_components.begin(), m_components.end(), to_remove[i]), m_components.end());
	}
	to_remove.clear();
}

void GameObject::update(float deltaTime) { }

Transform2D & GameObject::getTransform()
{
	return transform;
}

void GameObject::setColor(glm::vec4 color)
{
	this->color = color;
}

glm::vec4 GameObject::getColor()
{
	return color;
}

void GameObject::addComponent(Component2D * component)
{
	m_components.push_back(component);
	component->setTransform(&transform);
}

void GameObject::removeComponent(Component2D * component)
{
	to_remove.push_back(component);
}

void GameObject::destory()
{
	flagForDestory = true;
}

bool GameObject::isDestoryed()
{
	return flagForDestory;
}

void GameObject::setFont(aie::Font * font)
{
	this->font = font;
}

std::vector<Component2D*> GameObject::unSafeGetComponentsList()
{
	return m_components;
}
