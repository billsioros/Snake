
#pragma once

#include <types.hpp>

namespace Game
{
	struct Color3f
	{
		Game::coordinate_t red, green, blue;

		Color3f();

		Color3f(Game::coordinate_t red, Game::coordinate_t green, Game::coordinate_t blue);

		Color3f(const Color3f&);

		Color3f(Color3f&&) noexcept;

		Color3f& operator=(const Color3f&);

		Color3f& operator=(Color3f&&) noexcept;
	};
}
