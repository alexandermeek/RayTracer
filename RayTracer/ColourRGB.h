#ifndef COLOURRGB_H
#define COLOURRGB_H

class ColourRGB
{
	public:
		ColourRGB();
		ColourRGB(int r, int g, int b);
		~ColourRGB();

		ColourRGB operator* (const float k);
		ColourRGB operator+ (const ColourRGB colour);

		int r;
		int g;
		int b;

		std::string toString();
};
#endif // COLOURRGB_H
