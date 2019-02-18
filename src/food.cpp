
#include <food.hpp>

#include <vector>
#include <utility>
#include <cmath>

#include <GL/glut.h>

#define CIRCLE_STEP (0.0001f)

Game::Food::Food
(
    coordinate_t x, coordinate_t y, coordinate_t radius,
    const Color3f& stroke, const Color3f& fill
)
:
x(x), y(y), radius(radius), stroke(stroke), fill(fill)
{
}

Game::Food::Food(Food&& other) noexcept
:
x(std::move(other.x)), y(std::move(other.y)), radius(std::move(other.radius)),
stroke(std::move(other.stroke)), fill(std::move(other.fill))
{
}

Game::Food& Game::Food::operator=(Food&& other) noexcept
{
    x      = std::move(other.x);
    y      = std::move(other.y);
    radius = std::move(other.radius);

    stroke = std::move(other.stroke);
    radius = std::move(other.radius);

    return *this;
}

void Game::Food::render() const
{
    std::vector<point_t> points;
    for (coordinate_t angle = 0.0f; angle < 2.0f * M_PI; angle += CIRCLE_STEP)
        points.emplace_back(radius * std::cos(angle), radius * std::sin(angle));

    glPushMatrix();

    glTranslatef(x, y, 0.0f);

    glColor3f(fill.red, fill.green, fill.blue);

    glBegin(GL_POLYGON);

    for (const auto& point : points)
        glVertex2f(point.first, point.second);

    glEnd();

    glColor3f(stroke.red, stroke.green, stroke.blue);

    glBegin(GL_LINE_LOOP);

    for (const auto& point : points)
        glVertex2f(point.first, point.second);

    glEnd();

    glPopMatrix();
}
