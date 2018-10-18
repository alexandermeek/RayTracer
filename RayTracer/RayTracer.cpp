#include "pch.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Vector3D p0(0, 0, 0);
	Vector3D p1(0, 0, 10);

	int width = 5, height = width;
	Camera cam(p0, p1, width, height);
	cout << cam.toString() << endl;

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			cout << cam.getPixelPosition(i, j).toString() << endl;
		}
	}

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

		}
	}


	return 0;
}