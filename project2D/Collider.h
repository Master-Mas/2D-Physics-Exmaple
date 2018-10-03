#pragma once
#include "Component2D.h"
#include <Gizmos.h>

class Collider :
	public Component2D
{
public:
	static const unsigned int COLLIDER_SIZE = 2U;
	static const unsigned int COLLIDER_CIRCLE = 0U;
	static const unsigned int COLLIDER_PLANE = 1U;

	Collider(unsigned int type);
	~Collider();

	bool getDebug();
	void setDebug(bool debug);
	void setBouncePower(float bounce);
	float getBouncePower();

	virtual void drawGizmos() = 0;

	void draw(aie::Renderer2D* renderer) override;
	
	unsigned int getColliderType();
protected:
	bool debug = false;
	float bouncePower = 0.1f;

private:
	unsigned int colliderTypeID;
};

