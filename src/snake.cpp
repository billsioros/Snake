
#include <snake.hpp>
#include <window.hpp>

#include <utility>
#include <list>
#include <stdexcept>
#include <algorithm>

#include <GL/glut.h>

#define RERROR (1.0e-6f)

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
        case Keys::Down:  dx = +0.0f; dy = -size; break;
        case Keys::Up:    dx = +0.0f; dy = +size; break;
        case Keys::Right: dx = +size; dy = +0.0f; break;
        case Keys::Left:  dx = -size; dy = +0.0f; break;
        default:
            throw std::invalid_argument("The value of direction should be among [Keys::Down, Keys::Up, Keys::Right, Keys::Left]");
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
        case Keys::Down:  dx = +0.0f;      dy = -head.size; break;
        case Keys::Up:    dx = +0.0f;      dy = +head.size; break;
        case Keys::Right: dx = +head.size; dy = +0.0f;      break;
        case Keys::Left:  dx = -head.size; dy = +0.0f;      break;
    }

    #if defined (__VERBOSE__)
        std::printf("key: %c dx: %lf dy: %lf\n", direction, dx, dy);
    #endif
    
    if (head.x + head.size / 2.0f > Window::right())
        emplace_front(Window::left() + head.size / 2.0f, head.y + dy, head.size, head.stroke, head.fill);
    else if (head.x - head.size / 2.0f < Window::left())
        emplace_front(Window::right() - head.size / 2.0f, head.y + dy, head.size, head.stroke, head.fill);
    else if (head.y + head.size / 2.0f > Window::top())
        emplace_front(head.x + dx, Window::bottom() + head.size / 2.0f, head.size, head.stroke, head.fill);
    else if (head.y - head.size / 2.0f < Window::bottom())
        emplace_front(head.x + dx, Window::top() - head.size / 2.0f, head.size, head.stroke, head.fill);
    else
        emplace_front(head.x + dx, head.y + dy, head.size, head.stroke, head.fill);
        
    pop_back();
}

void Game::Snake::steer(direction_t direction)
{
    if
    (
        (this->direction == Keys::Down  && direction != Keys::Up)   ||
        (this->direction == Keys::Up    && direction != Keys::Down) ||
        (this->direction == Keys::Right && direction != Keys::Left) ||
        (this->direction == Keys::Left  && direction != Keys::Right)
    )
        this->direction = direction;
}

static inline float rand(float min, float max)
{
    return ((max - min) * static_cast<float>(std::rand()) /
    static_cast<float>(RAND_MAX) + min);
}

static inline int round(int number, int multiple)
{
    return (number / multiple) * multiple;
}

bool Game::Snake::ate(Food& food)
{
    const Cell& head = front();
    
    if
    (
        (head.x - head.size / 2.0f < food.x) && (food.x < head.x + head.size / 2.0f) &&
        (head.y - head.size / 2.0f < food.y) && (food.y < head.y + head.size / 2.0f)
    )
    {
        coordinate_t dx, dy;
        switch (direction)
        {
            case Keys::Down:  dx = +0.0f;      dy = -head.size; break;
            case Keys::Up:    dx = +0.0f;      dy = +head.size; break;
            case Keys::Right: dx = +head.size; dy = +0.0f;      break;
            case Keys::Left:  dx = -head.size; dy = +0.0f;      break;
        }

        const Cell& tail = back();

        emplace_back(tail.x + dx, tail.y + dy, tail.size, tail.stroke, tail.fill);

        auto predicate = [&food](const Cell& cell)
        {
            return std::abs(cell.x - food.x) < RERROR && std::abs(cell.y - food.y) < RERROR;
        };

        do
        {
            food.x = round(rand(Window::left(), Window::right()), head.size);
            food.y = round(rand(Window::bottom(), Window::top()), head.size);
        } while (std::find_if(begin(), end(), predicate) != end());

        #if defined (__VERBOSE__)
            std::printf("fx: %lf, fy: %lf\n", food.x, food.y);
        #endif

        return true;
    }

    return false;
}

bool Game::Snake::died() const
{
    const Cell& head = front();

    for (auto it = ++begin(); it != end(); ++it)
    {
        if
        (
            (head.x - head.size / 2.0f < it->x) && (it->x < head.x + head.size / 2.0f) &&
            (head.y - head.size / 2.0f < it->y) && (it->y < head.y + head.size / 2.0f)
        )
        {
            return true;
        }
    }

    return false;
}
