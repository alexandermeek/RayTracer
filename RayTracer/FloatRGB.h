#pragma once
class FloatRGB
{
	public:
		FloatRGB();
		FloatRGB(float r, float g, float b);
		~FloatRGB();

		FloatRGB operator* (const float k);
		FloatRGB operator* (const FloatRGB intensity);
		FloatRGB operator+ (const FloatRGB intensity);

		float r;
		float g;
		float b;

		std::string toString();
};

