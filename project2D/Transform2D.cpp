#include "Transform2D.h"
#include <iostream>

Transform2D::Transform2D()
{
	x = &(matrix[2][0]);
	y = &(matrix[2][1]);
}

Transform2D::~Transform2D()
{
}

glm::vec2 Transform2D::getPosition()
{
	return glm::vec2(*x, *y);
}

void Transform2D::setPosition(glm::vec2 pos)
{
	*x = pos.x;
	*y = pos.y;
	/*matrix[2][0] = pos.x;
	matrix[2][1] = pos.y;*/
}

void Transform2D::translate(glm::vec2 amount)
{
	*x += amount.x;
	*y += amount.y;
}

void Transform2D::rotate(float degrees)
{
	glm::mat3 mat;
	mat[0][0] = cosf(degrees);
	mat[0][1] = sinf(degrees);
	mat[1][0] = -sinf(degrees);
	mat[1][1] = cosf(degrees);

	matrix = matrix * mat;
}