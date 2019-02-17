
#pragma once

#include <game.hpp>
#include <cell.hpp>

#include <list>

namespace Game
{
    class Snake : public std::list<Game::Cell>
    {
        direction_t direction;

    public:

        Snake
        (
            coordinate_t x, coordinate_t y, coordinate_t size,
            direction_t direction,
            std::size_t length
        );

        Snake(const Snake&) = delete;

        Snake(Snake&&) noexcept;

        Snake& operator=(const Snake&) = delete;

        Snake& operator=(Snake&&) noexcept;

        void render() const;

        void update();

        void steer(direction_t key);
    };
}
