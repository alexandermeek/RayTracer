#pragma once
class FloatRGB
{
	public:
		FloatRGB();
		FloatRGB(float r, float g, float b);

		FloatRGB operator* (const float k);
		FloatRGB operator* (const FloatRGB intensity);
		FloatRGB operator+ (const FloatRGB intensity);

		float r;
		float g;
		float b;

		friend std::ostream& operator<<(std::ostream& os, const FloatRGB& rhs);
};

