//This is the Game.h File:

#ifndef __GAME__
#define __GAME__

#include "Vector2D.h"
#include <vector>

class Board;

//Snake Class:
class Snake {
private:
	std::vector<Vector2D> body;
	unsigned int speed;
	Vector2D direction;
	bool alive;

public:
	//Constructors:
	Snake(const unsigned int X, const unsigned int Y) : body(1, Vector2D(X,Y)), speed(1), direction(Vector2D::UP), alive(true) {};

	//Destructor:
	~Snake() { this->clearTail(); }

	//Accessors & Mutators:
	bool getAlive() const { return this->alive; }
	void setAlive(const bool state) { this->alive = state; }

	//Functionality:
	void clearTail() { if (!body.empty()) body.clear(); }
	void rotate(const Vector2D);
	void update();
	void eat();
	void constrain(const int , const int);
	bool intersects() const;
	bool collides(Board&) const;
	std::vector<Vector2D> getLocs() const;
};

//Board Class:
class Cell {
private:
	const Vector2D XY;
	const char RC;
	char VC;

public:
	static const char EMPTY = ' ';
	static const char WALL  = '#';
	static const char FOOD  = '$';
	static const char HEAD	= 'O';
	static const char TAIL	= 'o';

	//Constructors:
	Cell(const unsigned int X, const unsigned int Y, const char RC, const char VC) : XY(X, Y), RC(RC), VC(VC) {}
	Cell(Cell& other) : XY(other.XY), RC(other.RC), VC(other.VC) {}

	//Accessors & Mutators:
	Vector2D getXY() const { return this->XY; }
	char getVC() const { return this->VC; }
	void setVC(const char VC) { this->VC = VC; }

	//Functionality:
	void reset() { this->VC = this->RC; }
};

class Board {
private:
	unsigned int S;
	Cell*** T;
	bool failed;

public:
	//Constructor:
	Board(const char* const filename) : S(0), T(NULL), failed(false) { this->loadFromFile(filename); }

	//Destructor:
	~Board() { this->clear(); }

	//Accessors & Mutators:
	unsigned int size() const { return this->S; }
	Cell getCell(const unsigned int X, const unsigned int Y) const { return *this->T[Y][X]; }
	void setCell(const unsigned int X, const unsigned int Y, const char VC) { this->T[Y][X]->setVC(VC); }

	//Functionality:
	bool fail() const { return this->failed; }
	bool empty() const { return (this->S == 0); }
	void clear();
	void reset();
	void show() const;
	void loadFromFile(const char* const);
};

//Game Class:
class Level {
private:
	Board B;
	Snake S;
	Vector2D F;
	bool failed;

public:
	Level(const unsigned int);

	//Functionality:
	bool fail() const { return this->failed; }
	void update();
	void run();
	bool lost() const { return !this->S.getAlive(); }
};

class Game {
private:
	unsigned int No;
	Level* lvl;

public:
	Game() : No(1), lvl(new Level(1)) {}
	~Game() { delete this->lvl; }

	//Functionality:
	static Vector2D getMove();
	void run() const;
	void loadNextLevel();
	static void overScrn();
};

#endif