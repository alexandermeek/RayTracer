#include "pch.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Point3D p0(0, 0, 0);
	Point3D p1(10, 10, 0);

	Camera cam(p0, p1);
	cout << cam.toString();

	return 0;
}