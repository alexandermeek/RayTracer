#include "pch.h"
#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include "lodepng.h"

using std::cout;
using std::endl;

const std::string FILENAME = "redSphere.png";
const int M = 100; //Scale of image/scene
const int WIDTH = 1200; //Width of image 
const int HEIGHT = 1200; //Height of image
const float SCALE = 0.1; //Scale of the image;
const FloatRGB backgroundColour(50, 50, 50);

std::vector<short> image;
std::vector<Object3D*> objects;
FloatRGB maxValue;
FloatRGB minValue(INT32_MAX, INT32_MAX, INT32_MAX);

void savePixel(std::vector<short>& image, int i, int j, FloatRGB colour) {
	image[3 * WIDTH * j + 3 * i + 0] = colour.r;
	image[3 * WIDTH * j + 3 * i + 1] = colour.g;
	image[3 * WIDTH * j + 3 * i + 2] = colour.b;
}

void normaliseColours() {
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			image[3 * WIDTH * j + 3 * i + 0] = (image[3 * WIDTH * j + 3 * i + 0] - minValue.r) / (maxValue.r - minValue.r) * 255.0f;
			image[3 * WIDTH * j + 3 * i + 1] = (image[3 * WIDTH * j + 3 * i + 1] - minValue.g) / (maxValue.g - minValue.g) * 255.0f;
			image[3 * WIDTH * j + 3 * i + 2] = (image[3 * WIDTH * j + 3 * i + 2] - minValue.b) / (maxValue.b - minValue.b) * 255.0f;
		}
	}
}

int main() {
	Vector3D cameraPosition(0, 0, 500);
	Vector3D spherePosition1(0, 0, 0);
	Vector3D spherePosition2(20, 0, 30);
	Vector3D spherePosition3(0, 40, 50);
	Vector3D lightPosition(500, 500, 500);
	FloatRGB lightIntensity(0.8, 0.8, 0.8);

	Camera cam(cameraPosition, spherePosition1, WIDTH, HEIGHT, SCALE);
	PointLight light(lightPosition, lightIntensity);

	objects.push_back(new Sphere(spherePosition1, 40, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(spherePosition2, 20, FloatRGB(0, 0.25, 0), FloatRGB(0, 1, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(spherePosition3, 15, FloatRGB(0, 0, 0.25), FloatRGB(0, 0, 1), FloatRGB(0.5, 0.5, 0.5)));

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
				if (obj->intersect(objects, cam.getPixelPosition(i, j), cam.getVPN(), point, distance, light, colour)) {
					if (distance < tempDistance) {
						hit = true;
						tempDistance = distance;
						savePixel(image, i, j, colour);
					}
				}
			}
			if (!hit) {
				colour = backgroundColour;
				savePixel(image, i, j, colour);
			}
			maxValue.r = colour.r > maxValue.r ? colour.r : maxValue.r;
			maxValue.g = colour.g > maxValue.g ? colour.g : maxValue.g;
			maxValue.b = colour.b > maxValue.b ? colour.b : maxValue.b;
			minValue.r = colour.r < minValue.r ? colour.r : minValue.r;
			minValue.g = colour.g < minValue.g ? colour.g : minValue.g;
			minValue.b = colour.b < minValue.b ? colour.b : minValue.b;
		}
		cout << "\rProgress: " << (float) j / (float) HEIGHT * 100.00 << "%";
	}
	cout << "\rProgress: " << "100.00%" << endl;

	bool tooLarge = false;
	tooLarge = maxValue.r > 255 ? true : false;
	tooLarge = maxValue.g > 255 ? true : false;
	tooLarge = maxValue.b > 255 ? true : false;
	if (tooLarge) {
		cout << "Normalising colours...";
		normaliseColours();
		cout << "\rColours normalised! " << endl;
	} else {
		cout << "Not normalising colours." << endl;
	}

	cout << "Writing to file...        ";

	unsigned error = lodepng::encode(FILENAME, std::vector<unsigned char>(image.begin(), image.end()), WIDTH, HEIGHT,
		LodePNGColorType (LCT_RGB), unsigned (8));
	if (error) std::cout << endl << "encoder error " << error 
		<< ": " << lodepng_error_text(error) << std::endl;

	cout << "\rDone!             ";
	for (Object3D* obj : objects) {
		delete obj;
	}

	cout << endl << maxValue.toString() << " " << minValue.toString();
	return 0;
}

