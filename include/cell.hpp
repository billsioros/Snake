
#pragma once

#include <types.hpp>
#include <color3f.hpp>

namespace Game
{
	class Cell
	{
		friend class Snake;
		
		friend void Game::timer(int t);
		
		coordinate_t x, y, size;

		Color3f stroke, fill;

	public:

		Cell
		(
			coordinate_t x, coordinate_t y, coordinate_t size,
			const Color3f& stroke, const Color3f& fill
		);

		Cell(const Cell&) = delete;

		Cell(Cell&&) noexcept;

		Cell& operator=(const Cell&) = delete;

		Cell& operator=(Cell&&) noexcept;

		void render() const;
	};
}
