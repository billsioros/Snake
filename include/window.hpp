
#pragma once

#include <types.hpp>

#define X_WINDOW (0)
#define Y_WINDOW (0)
#define N_WINDOW ("Snake")
#define TIMESPAN (100U)

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
