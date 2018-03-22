//This is the Vector2D.cpp File:

#include "Vector2D.h"
#include "general.h"
#include <cstdlib>

using namespace std;
using namespace Integer;

//Directions:
const Vector2D Vector2D::UP(0, -1);
const Vector2D Vector2D::DOWN(0, 1);
const Vector2D Vector2D::RIGHT(1, 0);
const Vector2D Vector2D::LEFT(-1, 0);

void Vector2D::constrain(const int min, const int max)
{
	if (this->x < min)
		this->x = min;
	else if (this->x > max)
		this->x = max;

	if (this->y < min)
		this->y = min;
	else if (this->y > max)
		this->y = max;
}

Vector2D Vector2D::Random()
{
	const int r = RandomBetween(0, 10000);
	if (r <= 2500)
		return Vector2D(0, -1);	//UP
	else if (r <= 5000)
		return Vector2D(0, 1);	//DOWN
	else if (r <= 7500)
		return Vector2D(-1, 0); //LEFT
	else
		return Vector2D(1, 0);	//RIGHT
}

Vector2D Vector2D::Random(const int min, const int max)
{
	return Vector2D(RandomBetween(min, max), RandomBetween(min, max));
}

Vector2D Vector2D::Random(const int minX, const int maxX, const int minY, const int maxY)
{
	return Vector2D(RandomBetween(minX, maxX), RandomBetween(minY, maxY));
}
