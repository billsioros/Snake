
#pragma once

#define WEST  'a'
#define EAST  'd'
#define NORTH 'w'
#define SOUTH 's'

#define log(...) std::printf(__VA_ARGS__)

namespace Game
{
    using coordinate_t = float;

    using direction_t = char;

    namespace Window
    {
        extern coordinate_t width, height;
        
        inline coordinate_t left()   { return -Game::Window::width  / 2.0f; }
        inline coordinate_t right()  { return +Game::Window::width  / 2.0f; }
        inline coordinate_t bottom() { return -Game::Window::height / 2.0f; }
        inline coordinate_t top()    { return +Game::Window::height / 2.0f; }
    }
}
