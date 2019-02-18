
#pragma once

#include <types.hpp>

namespace Game
{
    namespace Window
    {
        extern coordinate_t width, height;
        
        inline coordinate_t left()   { return -width  / 2.0f; }
        inline coordinate_t right()  { return +width  / 2.0f; }
        inline coordinate_t bottom() { return -height / 2.0f; }
        inline coordinate_t top()    { return +height / 2.0f; }
    }
}
