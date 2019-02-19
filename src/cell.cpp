
#include <cell.hpp>

#include <utility>

#include <GL/glut.h>

Game::Cell::Cell
(
    coordinate_t x, coordinate_t y, coordinate_t size,
    const Color3f& stroke, const Color3f& fill
)
:
x(x), y(y), size(size), stroke(stroke), fill(fill)
{
}

Game::Cell::Cell(Cell&& other) noexcept
:
x(std::move(other.x)), y(std::move(other.y)), size(std::move(other.size)),
stroke(std::move(other.stroke)), fill(std::move(other.fill))
{
}

Game::Cell& Game::Cell::operator=(Cell&& other) noexcept
{
    x    = std::move(other.x);
    y    = std::move(other.y);
    size = std::move(other.size);

    stroke = std::move(other.stroke);
    fill   = std::move(other.fill);

    return *this;
}

void Game::Cell::render() const
{
    glColor3f(fill.red, fill.green, fill.blue);

    glRectf(x - size / 2.0f, y - size / 2.0f, x + size / 2.0f, y + size / 2.0f);

    glColor3f(stroke.red, stroke.green, stroke.blue);

    glBegin(GL_LINE_LOOP);

    glVertex2f(x - size / 2.0f , y - size / 2.0f);
    glVertex2f(x - size / 2.0f , y + size / 2.0f);
    glVertex2f(x + size / 2.0f , y + size / 2.0f);
    glVertex2f(x + size / 2.0f , y - size / 2.0f);

    glEnd();
}
