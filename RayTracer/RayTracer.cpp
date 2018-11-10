#include "pch.h"
#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include "lodepng.h"

using std::cout;
using std::endl;

const std::string FILENAME = "redSphere.png";
const int M = 100; //Scale of image
const int WIDTH = 12 * M; //Width of image 
const int HEIGHT = 12 * M; //Height of image

std::vector<unsigned char> image;
std::vector<Object3D*> objects;

void savePixel(std::vector<unsigned char>& image, int i, int j, FloatRGB colour) {
	image[3 * WIDTH * j + 3 * i + 0] = colour.r;
	image[3 * WIDTH * j + 3 * i + 1] = colour.g;
	image[3 * WIDTH * j + 3 * i + 2] = colour.b;
}

int main() {
	Vector3D cameraPosition(0, 0, 5000);
	Vector3D spherePosition1(0, 0, 0);
	Vector3D spherePosition2(2 * M, 0 * M, 3 * M);
	Vector3D spherePosition3(-2 * M, 2 * M, 2 * M);
	Vector3D lightPosition(5000, 5000, 5000);
	FloatRGB lightIntensity(0.5, 0.5, 0.5);

	Camera cam(cameraPosition, spherePosition1, WIDTH, HEIGHT); //Vector3D(60, 60, 0)
	PointLight light(lightPosition, lightIntensity);

	objects.push_back(new Sphere(spherePosition1, 4 * M, FloatRGB(0.1,0,0), FloatRGB(1,0,0), FloatRGB(0.5,0.5,0.5)));
	objects.push_back(new Sphere(spherePosition2, 2 * M, FloatRGB(0, 0.1, 0), FloatRGB(0, 1, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(spherePosition3, 2 * M, FloatRGB(0, 0, 0.1), FloatRGB(0, 0, 1), FloatRGB(0.5, 0.5, 0.5)));

	cout << cam.toString() << endl;
	cout << objects[0]->toString() << endl;
	
	image.resize(WIDTH * HEIGHT * 3);

	cout << std::fixed << std::setprecision(2);

	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			Vector3D point;
			float distance;
			float tempDistance = INT32_MAX;
			FloatRGB colour;
			bool hit = false;
			for (Object3D* obj : objects) {
				if (obj->intersect(cam.getPixelPosition(i, j), cam.getVPN(), point, distance, light, colour)) {
					if (distance < tempDistance) {
						hit = true;
						tempDistance = distance;
						savePixel(image, i, j, colour);
					}
				}
			}
			if (!hit) {
				savePixel(image, i, j, FloatRGB());
			}
		}
		cout << "\rProgress: " << (float) j / (float) HEIGHT * 100.00 << "%";
	}
	cout << "\rProgress: " << "100.00%" << endl;

	cout << "Writing to file...";
	unsigned error = lodepng::encode(FILENAME, image, WIDTH, HEIGHT, 
		LodePNGColorType (2), unsigned (8));
	if (error) std::cout << endl << "encoder error " << error 
		<< ": " << lodepng_error_text(error) << std::endl;

	cout << "\rDone!             ";
	for (Object3D* obj : objects) {
		delete obj;
	}
	return 0;
}

