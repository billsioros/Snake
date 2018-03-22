//This is the Vector2D.h File: "Simplistic Implementation of two dimensional Vectors in C++"

#ifndef __VECTOR2D__
#define __VECTOR2D__

class Vector2D {
private:
	int x;
	int y;

public:
	//Directions:
	static const Vector2D UP;
	static const Vector2D DOWN;
	static const Vector2D RIGHT;
	static const Vector2D LEFT;

	//Constructors:
	Vector2D(const int X, const int Y) : x(X), y(Y) {}

	//Copy Constructor:
	Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}

	//Accessors & Mutators:
	void setXY(const int X, const int Y) { this->x = X; this->y = Y; }
	void setX(const int X) { this->x = X; }
	void setY(const int Y) { this->y = Y; }
	int getX() const { return this->x; }
	int getY() const { return this->y; }

	//Overloaded Operators:
	Vector2D operator*(const int num) const { return Vector2D(this->x * num, this->y * num); }
	void operator*=(const int num) { this->x *= num; this->y *= num; }
	Vector2D operator+(const Vector2D& other) const { return Vector2D(this->x + other.x, this->y + other.y); }
	void operator+=(const Vector2D& other) { this->x += other.x; this->y += other.y; }
	void operator=(const Vector2D& other) { this->x = other.x; this->y = other.y; }
	bool operator==(const Vector2D& other) const { return (this->x == other.x && this->y == other.y); }
	bool operator!=(const Vector2D& other) const { return (this->x != other.x || this->y != other.y); }

	//Functionality:
	void constrain(const int, const int);
	static Vector2D Random();
	static Vector2D Random(const int min, const int max);
	static Vector2D Random(const int minX, const int maxX, const int minY, const int maxY);
};

#endif