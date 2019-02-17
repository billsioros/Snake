
#pragma once

#include <game.hpp>

namespace Game
{
	class Cell
	{
		friend class Snake;
		
		coordinate_t x, y, size;

	public:

		Cell(coordinate_t x, coordinate_t y, coordinate_t size);

		Cell(const Cell&) = delete;

		Cell(Cell&&) noexcept;

		Cell& operator=(const Cell&) = delete;

		Cell& operator=(Cell&&) noexcept;

		void render() const;
	};
}
