
#pragma once

namespace Game
{
	struct Color3f
	{
		float red, green, blue;

		Color3f();

		Color3f(float red, float green, float blue);

		Color3f(const Color3f&);

		Color3f(Color3f&&) noexcept;

		Color3f& operator=(const Color3f&);

		Color3f& operator=(Color3f&&) noexcept;
	};
}
