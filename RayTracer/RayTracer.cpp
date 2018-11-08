#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;

const std::string FILENAME = "redSphere";

int main() {
	Vector3D cameraPosition(0, 0, 500);
	Vector3D spherePosition(0, 0, 0);
	Vector3D lightPosition(500, 500, 500);

	const int width = 300;
	const int height = 200;
	const int radius = 60;
	Camera cam(cameraPosition, spherePosition, width, height);
	Sphere sph(spherePosition, radius, ColourRGB(255, 0 ,0));

	cout << cam.toString() << endl;
	cout << sph.toString() << endl;

	ofstream imageFile;
	imageFile.open(FILENAME + ".ppm");
	
	std::vector<unsigned char> image;
	image.resize(width * height * 3);

	imageFile << "P3" << endl
		<< width << endl
		<< height << endl
		<< 255 << endl;
	ColourRGB c;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (sph.intersect(cam.getPixelPosition(i, j), cam.getVPN(), lightPosition, c)) {
				imageFile << c.toString() << endl;
				image[3 * width * j + 3 * i + 0] = c.r;
				image[3 * width * j + 3 * i + 0] = c.g;
				image[3 * width * j + 3 * i + 0] = c.b;

			} else {
				imageFile << "0 0 0" << endl;
				image[3 * width * j + 3 * i + 0] = 0;
				image[3 * width * j + 3 * i + 0] = 0;
				image[3 * width * j + 3 * i + 0] = 0;
			}
		}
		cout << "\rProgress: " << (float)j / (float)height * 100.00 << "%     ";
	}
	imageFile.close();

	cout << endl << "Done!";
	return 0;
}