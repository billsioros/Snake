
#include <snake.hpp>

#include <utility>
#include <list>
#include <stdexcept>

#include <GL/glut.h>

Game::Snake::Snake
(
    coordinate_t x, coordinate_t y, coordinate_t size,
    direction_t direction,
    std::size_t length
)
:
direction(direction)
{
    coordinate_t dx, dy;
    switch (direction)
    {
        case SOUTH: dx = +0.0f; dy = -size; break;
        case NORTH: dx = +0.0f; dy = +size; break;
        case EAST:  dx = +size; dy = +0.0f; break;
        case WEST:  dx = -size; dy = +0.0f; break;
        default:
            throw std::invalid_argument("The value of direction should be among [SOUTH, NORTH, EAST, WEST]");
    }

    emplace_front(x, y, size);

    for (std::size_t i = 0UL; i < length - 1UL; i++)
    {
        const Cell& cell = front();

        emplace_front(cell.x + dx, cell.y + dy, cell.size);
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
    for (const auto& cell : *this)
        cell.render();
}

void Game::Snake::update()
{
    const Cell& cell = front();

    coordinate_t dx, dy;
    switch (direction)
    {
        case SOUTH: dx = +0.0f;  dy = -cell.size; break;
        case NORTH: dx = +0.0f;  dy = +cell.size; break;
        case EAST:  dx = +cell.size; dy = +0.0f;  break;
        case WEST:  dx = -cell.size; dy = +0.0f;  break;
    }

    #if defined (__VERBOSE__)
        log("key: %c dx: %lf dy: %lf\n", direction, dx, dy);
    #endif
    
    if (cell.x + cell.size + dx > Window::right())
        emplace_front(Window::left(), cell.y + dy, cell.size);
    else if (cell.x + dx < Window::left())
        emplace_front(Window::right(), cell.y + dy, cell.size);
    else if (cell.y + cell.size + dy > Window::top())
        emplace_front(cell.x + dx, Window::bottom(), cell.size);
    else if (cell.y + dy < Window::bottom())
        emplace_front(cell.x + dx, Window::top(), cell.size);
    else
        emplace_front(cell.x + dx, cell.y + dy, cell.size);
        
    pop_back();
}

void Game::Snake::steer(direction_t direction)
{
    if
    (
        direction == SOUTH ||
        direction == NORTH ||
        direction == EAST  ||
        direction == WEST
    )
        this->direction = direction;
}
