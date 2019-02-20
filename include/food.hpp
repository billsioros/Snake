
#pragma once

#include <types.hpp>
#include <color3f.hpp>

namespace Game
{
	class Food
	{
		friend class Snake;
		
		friend void Game::timer(int t);
		
		coordinate_t x, y, radius;

		Color3f stroke, fill;
		
	public:

		Food
		(
			coordinate_t x, coordinate_t y, coordinate_t radius,
			const Color3f& stroke, const Color3f& fill
		);

		Food(const Food&) = delete;

		Food(Food&&) noexcept;

		Food& operator=(const Food&) = delete;

		Food& operator=(Food&&) noexcept;

		void render() const;
	};
}
