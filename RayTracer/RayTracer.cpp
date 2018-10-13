#include "pch.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	Vector3D v(0, 1, 0);
	cout << v.magnitude() << " " << v.toString() << endl;

	Vector3D u(1, 0, 0);
	cout << u.magnitude() << " " << u.toString() << endl;

	cout << v.cosTheta(u);

	return 0;
}