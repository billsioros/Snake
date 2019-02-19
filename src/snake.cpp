
#include <snake.hpp>
#include <window.hpp>

#include <utility>
#include <list>
#include <stdexcept>

#include <GL/glut.h>

Game::Snake::Snake
(
    coordinate_t x, coordinate_t y, coordinate_t size,
    direction_t direction,
    std::size_t length,
    const Color3f& stroke, const Color3f& fill
)
:
direction(direction)
{
    coordinate_t dx, dy;
    switch (direction)
    {
        case Game::Keys::Down: dx = +0.0f; dy = -size; break;
        case Game::Keys::Up: dx = +0.0f; dy = +size; break;
        case Game::Keys::Right:  dx = +size; dy = +0.0f; break;
        case Game::Keys::Left:  dx = -size; dy = +0.0f; break;
        default:
            throw std::invalid_argument("The value of direction should be among [Game::Keys::Down, Game::Keys::Up, Game::Keys::Right, Game::Keys::Left]");
    }

    emplace_front(x, y, size, stroke, fill);

    for (std::size_t i = 0UL; i < length - 1UL; i++)
    {
        const Cell& head = front();

        emplace_front(head.x + dx, head.y + dy, size, head.stroke, head.fill);
    }
}

Game::Snake::Snake(Snake&& other) noexcept
:
std::list<Cell>(std::move(other)),
direction(std::move(other.direction))
{
}

Game::Snake& Game::Snake::operator=(Snake&& other) noexcept
{
    std::list<Cell>::operator=(std::move(other));

    direction = std::move(other.direction);

    return *this;
}

void Game::Snake::render() const
{
    glColor3f(0.1f, 1.0f, 0.1f);

    for (const auto& cell : *this)
        cell.render();
}

void Game::Snake::update()
{
    const Cell& head = front();

    coordinate_t dx, dy;
    switch (direction)
    {
        case Game::Keys::Down:  dx = +0.0f;      dy = -head.size; break;
        case Game::Keys::Up:    dx = +0.0f;      dy = +head.size; break;
        case Game::Keys::Right: dx = +head.size; dy = +0.0f;      break;
        case Game::Keys::Left:  dx = -head.size; dy = +0.0f;      break;
    }

    #if defined (__VERBOSE__)
        std::printf("key: %c dx: %lf dy: %lf\n", direction, dx, dy);
    #endif
    
    if (head.x + head.size / 2.0f > Game::Window::right())
        emplace_front(Game::Window::left() + head.size / 2.0f, head.y + dy, head.size, head.stroke, head.fill);
    else if (head.x - head.size / 2.0f < Game::Window::left())
        emplace_front(Game::Window::right() - head.size / 2.0f, head.y + dy, head.size, head.stroke, head.fill);
    else if (head.y + head.size / 2.0f > Game::Window::top())
        emplace_front(head.x + dx, Game::Window::bottom() + head.size / 2.0f, head.size, head.stroke, head.fill);
    else if (head.y - head.size / 2.0f < Game::Window::bottom())
        emplace_front(head.x + dx, Game::Window::top() - head.size / 2.0f, head.size, head.stroke, head.fill);
    else
        emplace_front(head.x + dx, head.y + dy, head.size, head.stroke, head.fill);
        
    pop_back();
}

void Game::Snake::steer(direction_t direction)
{
    if
    (
        direction == Game::Keys::Down  ||
        direction == Game::Keys::Up    ||
        direction == Game::Keys::Right ||
        direction == Game::Keys::Left
    )
        this->direction = direction;
}

bool Game::Snake::ate(const Food& food) const
{
    const Cell& head = front();
    
    return
    (
        (head.x - head.size / 2.0f < food.x) && (food.x < head.x + head.size / 2.0f) &&
        (head.y - head.size / 2.0f < food.y) && (food.y < head.y + head.size / 2.0f)
    );
}
