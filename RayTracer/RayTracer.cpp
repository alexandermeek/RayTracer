#include "pch.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

int main() {
	Vector3D p0(0, 0, 500);
	Vector3D p1(0, 0, 0);

	const int width = 300;
	const int height = 200;
	const int radius = 60;
	Camera cam(p0, p1, width, height);
	Sphere sph(p1, radius, ColourRGB(255, 0 ,0));

	cout << cam.toString() << endl;
	cout << sph.toString() << endl;

	ofstream imageFile;
	imageFile.open("redSphere.ppm");

	imageFile << "P3" << endl
		<< width << endl
		<< height << endl
		<< 255 << endl;
	ColourRGB c;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (sph.intersect(cam.getPixelPosition(i, j), cam.getVPN(), c)) {
				imageFile << c.r <<  " " << c.g << " " << c.b << endl;
			}
			else {
				imageFile << "0 0 0" << endl;
			}
		}
		cout << "\rProgress: " << (float)j / (float)height * 100.00 << "%     ";
	}
	imageFile.close();
	cout << endl << "Done!";
	return 0;
}