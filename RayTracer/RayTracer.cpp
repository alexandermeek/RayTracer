#include "pch.h"
#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include "lodepng.h"

using std::cout;
using std::endl;

const std::string FILENAME = "redSphere";

ColourRGB getColourValue(Object3D* obj, Vector3D point, Vector3D lightPos) {
	Vector3D normal = obj->getNormal(point);
	Vector3D lightDirection = (point - lightPos).unitVector();

	ColourRGB colour = obj->getColour() * obj->getKA() 
		+ obj->getColour() * normal.dotProduct(lightDirection) * obj->getKD();

	return colour;
}

int main() {
	Vector3D cameraPosition(0, 0, 5000);
	Vector3D spherePosition(0, 0, 0);
	Vector3D lightPosition(5000, 5000, 5000);

	const int multiplier = 100;
	const int width = 30*multiplier;
	const int height = 20*multiplier;
	const int radius = 6*multiplier;
	Camera cam(cameraPosition, spherePosition, width, height);
	Object3D *sph = new Sphere(spherePosition, radius, ColourRGB(255, 0 ,0), 0.25, 0.75, 0);

	cout << cam.toString() << endl;
	cout << sph->toString() << endl;
	
	std::vector<unsigned char> image;
	image.resize(width * height * 3);

	cout << std::fixed << std::setprecision(2);

	Vector3D point;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (sph->intersect(cam.getPixelPosition(i, j), cam.getVPN(), point)) {
				ColourRGB c = getColourValue(sph, point, lightPosition);
				image[3 * width * j + 3 * i + 0] = c.r;
				image[3 * width * j + 3 * i + 1] = c.g;
				image[3 * width * j + 3 * i + 2] = c.b;
			} else {
				image[3 * width * j + 3 * i + 0] = 0;
				image[3 * width * j + 3 * i + 1] = 0;
				image[3 * width * j + 3 * i + 2] = 0;
			}
		}
		cout << "\rProgress: " << (float) j / (float) height * 100.00 << "%";
	}

	unsigned error = lodepng::encode(FILENAME + ".png", image, width, height, 
		LodePNGColorType (2), unsigned (8));
	if (error) std::cout << endl << "encoder error " << error 
		<< ": " << lodepng_error_text(error) << std::endl;

	cout << endl << "Done!";
	return 0;
}

