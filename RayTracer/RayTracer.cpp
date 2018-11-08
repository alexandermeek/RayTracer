#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "lodepng.h"

using std::cout;
using std::endl;
//using std::ofstream;



const std::string FILENAME = "redSphere";

int main() {
	Vector3D cameraPosition(0, 0, 5000);
	Vector3D spherePosition(0, 0, 0);
	Vector3D lightPosition(5000, 5000, 5000);

	const int width = 3000;
	const int height = 2000;
	const int radius = 600;
	Camera cam(cameraPosition, spherePosition, width, height);
	Sphere sph(spherePosition, radius, ColourRGB(255, 0 ,0), 0.25, 0.75, 0);

	cout << cam.toString() << endl;
	cout << sph.toString() << endl;
	
	std::vector<unsigned char> image;
	image.resize(width * height * 3);

	ColourRGB c;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (sph.intersect(cam.getPixelPosition(i, j), cam.getVPN(), lightPosition, c)) {
				image[3 * width * j + 3 * i + 0] = c.r;
				image[3 * width * j + 3 * i + 1] = c.g;
				image[3 * width * j + 3 * i + 2] = c.b;
			} else {
				image[3 * width * j + 3 * i + 0] = 0;
				image[3 * width * j + 3 * i + 1] = 0;
				image[3 * width * j + 3 * i + 2] = 0;
			}
		}
		cout << "\rProgress: " << (float) j / (float) height * 100.00 << "%     ";
	}

	unsigned error = lodepng::encode(FILENAME + ".png", image, width, height, LodePNGColorType (2), unsigned (8));
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	cout << endl << "Done!";
	return 0;
}