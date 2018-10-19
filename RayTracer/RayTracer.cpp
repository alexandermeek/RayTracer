#include "pch.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

int main() {
	Vector3D p0(0, 0, 50);
	Vector3D p1(0, 0, 0);

	const int width = 300;
	const int height = 200;
	const int radius = 60;
	Camera cam(p0, p1, width, height);
	Sphere sph(p1, radius);
	int image [width*height];

	cout << cam.toString() << endl;
	cout << sph.toString() << endl;

	ofstream imageFile;
	imageFile.open("redSphere.ppm");

	imageFile << "P3" << endl
		<< width << endl
		<< height << endl
		<< 255 << endl;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (sph.doesIntersect(cam.getPixelPosition(i, j), cam.getVPN())) {
				image[i + j * width] = 255;
			}
			else {
				image[i + j * width] = 0;
			}
			imageFile << image[i + j * width] << " 0 0" << endl;
			//cout << image[i + j * width] << " ";
		}
		//cout << endl;
	}
	imageFile.close();
	return 0;
}