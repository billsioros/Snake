
#pragma once

#include <utility>

namespace Game
{
    using coordinate_t = float;

    using point_t = std::pair<coordinate_t, coordinate_t>;

    using direction_t = char;

    enum Keys { Left = 'a', Right = 'd', Up = 'w', Down = 's' };
}
