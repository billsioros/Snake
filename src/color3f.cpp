
#include <color3f.hpp>

#include <utility>

Game::Color3f::Color3f()
:
red(0.0f), green(0.0f), blue(0.0f)
{
}

Game::Color3f::Color3f(float red, float green, float blue)
:
red(red), green(green), blue(blue)
{
}

Game::Color3f::Color3f(const Color3f& other)
:
red(other.red), green(other.green), blue(other.blue)
{
}

Game::Color3f::Color3f(Color3f&& other) noexcept
:
red(std::move(other.red)), green(std::move(other.green)), blue(std::move(other.blue))
{
}

Game::Color3f& Game::Color3f::operator=(const Color3f& other)
{
    red   = other.red;
    green = other.green;
    blue  = other.blue;

    return *this;
}

Game::Color3f& Game::Color3f::operator=(Color3f&& other) noexcept
{
    red   = std::move(other.red);
    green = std::move(other.green);
    blue  = std::move(other.blue);

    return *this;
}
