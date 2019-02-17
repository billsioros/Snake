
#include <cell.hpp>

#include <utility>

#include <GL/glut.h>

Game::Cell::Cell(coordinate_t x, coordinate_t y, coordinate_t size)
:
x(x), y(y), size(size)
{
}

Game::Cell::Cell(Cell&& other) noexcept
:
x(std::move(other.x)), y(std::move(other.y)), size(std::move(other.size))
{
}

Game::Cell& Game::Cell::operator=(Cell&& other) noexcept
{
    x    = std::move(other.x);
    y    = std::move(other.y);
    size = std::move(other.size);

    return *this;
}

void Game::Cell::render() const
{
    glBegin(GL_LINE_LOOP);

    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);

    glEnd();
}
