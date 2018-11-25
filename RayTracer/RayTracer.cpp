#include "pch.h"
#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include "lodepng.h"

using std::cout;
using std::endl;

const std::string FILENAME = "redSphere.png";
const int WIDTH = 120; //Width of image 
const int HEIGHT = 120; //Height of image
const float SCALE = 1; //Scale of the image;
const FloatRGB backgroundColour(10, 10, 10);

std::vector<unsigned short> image;
std::vector<Object3D*> objects;

float maxValue;
float minValue = INT32_MAX;

void savePixel(std::vector<unsigned short>& image, int i, int j, FloatRGB colour) {
	image[3 * WIDTH * j + 3 * i + 0] = colour.r;
	image[3 * WIDTH * j + 3 * i + 1] = colour.g;
	image[3 * WIDTH * j + 3 * i + 2] = colour.b;
}

void normaliseColours() {
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			image[3 * WIDTH * j + 3 * i + 0] = (image[3 * WIDTH * j + 3 * i + 0] - minValue) / (maxValue - minValue) * 255.0f;
			image[3 * WIDTH * j + 3 * i + 1] = (image[3 * WIDTH * j + 3 * i + 1] - minValue) / (maxValue - minValue) * 255.0f;
			image[3 * WIDTH * j + 3 * i + 2] = (image[3 * WIDTH * j + 3 * i + 2] - minValue) / (maxValue - minValue) * 255.0f;
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

	//Original scene.
	/*objects.push_back(new Sphere(spherePosition1, 40, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(spherePosition2, 20, FloatRGB(0, 0.25, 0), FloatRGB(0, 1, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(spherePosition3, 15, FloatRGB(0, 0, 0.25), FloatRGB(0, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(Vector3D(0,0,50), Vector3D(20, 0, 50), Vector3D(0, 40, 50), FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));*/

	//Dodecahedron object.
	/*Vector3D v1(-0.57735, -0.57735, 0.57735); Vector3D v2(0.934172, 0.356822, 0);
	Vector3D v3(0.934172, -0.356822, 0); Vector3D v4(-0.934172, 0.356822, 0);
	Vector3D v5(-0.934172, -0.356822, 0); Vector3D v6(0, 0.934172, 0.356822);
	Vector3D v7(0, 0.934172, -0.356822); Vector3D v8(0.356822, 0, -0.934172);
	Vector3D v9(-0.356822, 0, -0.934172); Vector3D v10(0, -0.934172, -0.356822);
	Vector3D v11(0, -0.934172, 0.356822); Vector3D v12(0.356822, 0, 0.934172);
	Vector3D v13(-0.356822, 0, 0.934172); Vector3D v14(0.57735, 0.57735, -0.57735);
	Vector3D v15(0.57735, 0.57735, 0.57735); Vector3D v16(-0.57735, 0.57735, -0.57735);
	Vector3D v17(-0.57735, 0.57735, 0.57735); Vector3D v18(0.57735, -0.57735, -0.57735);
	Vector3D v19(0.57735, -0.57735, 0.57735); Vector3D v20(-0.57735, -0.57735, -0.57735);

	objects.push_back(new Triangle3D(v19, v3, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v12, v19, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v15, v12, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v8, v14, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v18, v8, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v3, v18, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v20, v5, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v9, v20, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v16, v9, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v13, v17, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v13, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v5, v1, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v7, v16, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v7, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v17, v6, v4, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v15, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v7, v6, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v14, v17, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v10, v18, v3, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v11, v10, v3, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v19, v11, v3, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v11, v1, v5, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v10, v11, v5, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v20, v10, v5, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v20, v9, v8, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v10, v20, v8, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v18, v10, v8, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v9, v16, v7, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v8, v9, v7, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v14, v8, v7, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v12, v15, v6, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v13, v12, v6, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v17, v13, v6, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v13, v1, v11, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v12, v13, v11, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v19, v12, v11, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));*/


	//Diamond object.
	/*Vector3D v1(0, 0, 78.0000); Vector3D v2(45.0000, 45.0000, 0);
	Vector3D v3(45.0000, -45.0000, 0); Vector3D v4(-45.0000, -45.0000, 0);
	Vector3D v5(-45.0000, 45.0000, 0); Vector3D v6(0, 0, -78.0000);

	objects.push_back(new Triangle3D(v1, v2, v3, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v3, v4, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v4, v5, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v5, v2, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v5, v4, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v4, v3, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v3, v2, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v2, v1, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v1, v5, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));*/

	Vector3D v1(20, 20, 0);
	Vector3D v2(-20, 20, 0);
	Vector3D v3(-20, -20, 0);
	Vector3D v4(20, -20, 0);

	objects.push_back(new Triangle3D(v1, v2, v3, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v3, v4, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));

	cout << cam.toString() << endl;
	for (Object3D* obj : objects) {
		cout << obj->toString() << endl;
	}

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
			maxValue = colour.r > maxValue ? colour.r : maxValue;
			maxValue = colour.g > maxValue ? colour.g : maxValue;
			maxValue = colour.b > maxValue ? colour.b : maxValue;
			minValue = colour.r < minValue ? colour.r : minValue;
			minValue = colour.g < minValue ? colour.g : minValue;
			minValue = colour.b < minValue ? colour.b : minValue;
		}
		cout << "\rProgress: " << (float) j / (float) HEIGHT * 100.00 << "%";
	}
	cout << "\rProgress: " << "100.00%" << endl;

	if (maxValue > 255) {
		cout << "Normalising colours...";
		normaliseColours();
		cout << "\rColours normalised!   " << endl;
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
	return 0;
}

