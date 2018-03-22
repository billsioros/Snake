//This is the Game.cpp File:

#include "Game.h"
#include "general.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

int _kbhit() {
	static const int STDIN = 0;
	static bool initialized = false;

	if (!initialized) {
		termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initialized = true;
	}

	int bytesWaiting;
	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}

int _getch()
{
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}

using namespace std;

void Snake::rotate(const Vector2D dir)
{
	if (dir != Vector2D::UP && dir != Vector2D::DOWN && dir != Vector2D::RIGHT && dir != Vector2D::LEFT) return;

	this->direction = dir;
}

void Snake::update()
{
	Vector2D prevLoc(this->body[0].getX(), this->body[0].getY());
	this->body[0] += (this->direction * speed);

	for (size_t i = 1; i < this->body.size(); i++) {
		Vector2D temp(this->body[i].getX(), this->body[i].getY());
		this->body[i] = prevLoc;
		prevLoc = temp;
	}
}

void Snake::eat()
{
	this->body.push_back(Vector2D(0, 0));
}

void Snake::constrain(const int min, const int max)
{
	this->body[0].constrain(min, max);
}

bool Snake::intersects() const
{
	for (size_t i = 1; i < this->body.size(); i++) {
		if (this->body[0] == this->body[i])
			return true;
	}

	return false;
}

bool Snake::collides(Board& B) const
{
	return (B.getCell(this->body[0].getX(), this->body[0].getY()).getVC() == Cell::WALL);
}

vector<Vector2D> Snake::getLocs() const
{
	vector<Vector2D> rv;
	for (size_t i = 0; i < this->body.size(); i++) {
		rv.push_back(this->body[i]);
	}

	return rv;
}

void Board::clear()
{
	if (!this->empty()) {
		for (unsigned int y = 0; y < this->S; y++) {
			for (unsigned int x = 0; x < this->S; x++)
				delete T[y][x];

			delete[] T[y];
		}

		delete[] T;

		this->T = NULL;
		this->S = 0;
	}
}

void Board::reset()
{
	for (unsigned int y = 0; y < S; y++)
		for (unsigned int x = 0; x < S; x++)
			T[y][x]->reset();
}

void Board::show() const
{
	for (unsigned int y = 0; y < S; y++) {
		for (unsigned int x = 0; x < S; x++)
			cout << T[y][x]->getVC();

		cout << endl;
	}
}

void Board::loadFromFile(const char* const filename)
{
	//Load Level File:
	ifstream ifs(filename);
	if (ifs.fail()) {
		cerr << "< " << filename << " >: Failed to open..." << endl;
		this->failed = true;

		return;
	}

	//Store the File's contents in a vector of strings:
	vector<string> Lines;
	do {
		string current; getline(ifs, current);

		if (!current.empty() && current[0] != '/' && current[1] != '/') Lines.push_back(current);
	} while (!ifs.eof());

	//Clear the Board in order to avoid memory leaks:
	this->clear();

	//Populate the Board based on the vector's contents:
	this->S = Lines.size();

	this->T = new Cell**[this->S];
	for (unsigned int y = 0; y < S; y++) {
		this->T[y] = new Cell*[this->S];
		for (unsigned int x = 0; x < S; x++)
			this->T[y][x] = new Cell(x, y, (Lines[y][x] != Cell::WALL ? Cell::EMPTY : Cell::WALL), Lines[y][x]);
	}

	this->failed = false;
}

Level::Level(const unsigned int lvl)
	:
	B(("../src/Level_" + Integer::toString(lvl) + ".txt").c_str()),
	S(this->B.size() / 2, this->B.size() / 2),
	F(Vector2D::Random(0, this->B.size() - 1)),
	failed(this->B.fail())
{
}

void Level::update()
{
	this->B.reset();

	vector<Vector2D> loc(this->S.getLocs());
	int x = loc[0].getX(), y = loc[0].getY();
	this->B.setCell(x, y, Cell::HEAD);

	for (size_t i = 1; i < loc.size(); i++) {
		const int x = loc[i].getX(), y = loc[i].getY();
		this->B.setCell(x, y, Cell::TAIL);
	}

	x = this->F.getX(), y = this->F.getY();
	this->B.setCell(x, y, Cell::FOOD);
}

void Level::run()
{
	this->update();
	this->B.show();

	this->S.rotate(Game::getMove());
	this->S.update();
	this->S.constrain(0, this->B.size() - 1);

	if (this->S.getLocs()[0] == this->F) {
		this->F = Vector2D::Random(0, this->B.size() - 1);
		this->S.eat();
	}

	if (this->S.intersects() || this->S.collides(this->B)) this->S.setAlive(false);

	usleep(150000);
	Other::clrscrn();
}

Vector2D Game::getMove()
{
	if (_kbhit()) {
		switch (tolower(_getch()))
		{
			case 'w': return Vector2D::UP;
			case 's': return Vector2D::DOWN;
			case 'd': return Vector2D::RIGHT;
			case 'a': return Vector2D::LEFT;
		}
	}

	return Vector2D(0, 0);
}

void Game::run() const
{
	while (!this->lvl->fail() && !this->lvl->lost())
		this->lvl->run();

	Game::overScrn();
}

void Game::loadNextLevel()
{
	this->lvl = new Level(++this->No);
}

void Game::overScrn()
{
	cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t***GAME OVER***\n\n\n\n\n\n\n" << endl;
}