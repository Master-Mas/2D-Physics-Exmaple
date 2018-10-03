#pragma once

#include <glm\glm.hpp>
#include <glm\ext.hpp>

class Transform2D
{
public:
	Transform2D();
	~Transform2D();

	//Position
	glm::vec2 getPosition();
	void setPosition(glm::vec2);
	void translate(glm::vec2);

	void rotate(float degrees);

private:
	glm::mat3 matrix;
	float* x;
	float* y;
};
