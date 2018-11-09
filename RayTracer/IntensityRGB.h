#pragma once
class IntensityRGB
{
	public:
		IntensityRGB();
		IntensityRGB(float r, float g, float b);
		~IntensityRGB();

		IntensityRGB operator* (const float k);
		IntensityRGB operator+ (const IntensityRGB intensity);

		float r;
		float g;
		float b;

		std::string toString();
};

