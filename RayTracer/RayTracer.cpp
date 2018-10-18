#include "pch.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Vector3D p0(0, 0, 50);
	Vector3D p1(0, 0, 0);

	int width = 20, height = 20;
	int radius = 6;
	Camera cam(p0, p1, width, height);
	Sphere sph(p1, radius);
	float image [400];

	cout << cam.toString() << endl;
	cout << sph.toString() << endl;

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			if (sph.doesIntersect(cam.getPixelPosition(i, j), cam.getVPN())) {
				image[i * height + j] = 1;
			}
			else {
				image[i * height + j] = 0;
			}
			cout << image[i * height + j] << " ";
		}
		cout << endl;
	}
	return 0;
}