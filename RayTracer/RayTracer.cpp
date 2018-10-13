#include "pch.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Vector3D v(0, 1, 0);
	cout << v.magnitude() << " " << v.toString() << endl;

	Vector3D u(1, 0, 0);
	cout << u.magnitude() << " " << u.toString() << endl;

	cout << v.cosTheta(u) << endl;

	Point3D p1(1, 1, 1);
	cout << p1.toString() << endl;

	Point3D p2(1, 1, 6);
	cout << p2.toString() << endl;

	Vector3D s;
	s = p2 - p1;
	cout << s.toString();

	return 0;
}