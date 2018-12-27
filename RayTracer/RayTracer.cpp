#include "pch.h"
#include <iostream>
#include <iomanip> // setprecision
#include <vector>

#include <ctime> //Timings
#include <omp.h> //Parallelism
#include "lodepng.h" //Save as png
#include <mutex> //mutex lock

using std::cout;
using std::endl;

const std::string FILENAME = "render.png";
const std::string LOG_FILENAME = "log.txt";

//To keep the same composition in frame if you multiply the width by X, divide the scale by X.
const int WIDTH = 100; //Width of image 
const int HEIGHT = 100; //Height of image
const float SCALE = 0.24; //Scale of the image;
const FloatRGB backgroundColour(30, 30, 30);

std::vector<unsigned short> image;
std::vector<Object3D*> objects;
std::vector<Vector3D> vertices;

float maxValue;
float minValue = INT32_MAX;

std::mutex progressLock;
std::mutex raysMissedLock;
int progress = 0;
int old_bar = -1;
int num_rays_missed = 0;

void savePixel(std::vector<unsigned short>& image, int i, int j, FloatRGB colour) {
	image[3 * WIDTH * j + 3 * i + 0] = colour.r;
	image[3 * WIDTH * j + 3 * i + 1] = colour.g;
	image[3 * WIDTH * j + 3 * i + 2] = colour.b;
}

void normaliseColours() {
	#pragma omp parallel for
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			image[3 * WIDTH * j + 3 * i + 0] = (image[3 * WIDTH * j + 3 * i + 0] - minValue) / (maxValue - minValue) * 255.0f;
			image[3 * WIDTH * j + 3 * i + 1] = (image[3 * WIDTH * j + 3 * i + 1] - minValue) / (maxValue - minValue) * 255.0f;
			image[3 * WIDTH * j + 3 * i + 2] = (image[3 * WIDTH * j + 3 * i + 2] - minValue) / (maxValue - minValue) * 255.0f;
		}
	}
}

void saveProgress(int max) {
	progressLock.lock();
	int barWidth = 50;

	progress++;
	float tempProgress = (float)progress / (float)HEIGHT;

	if (int(tempProgress * 100) % 2 == 0) {
		int pos = barWidth * tempProgress;
		if (old_bar != pos) {
			old_bar = pos;
			cout << "Progress: [";
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) cout << "=";
				else if (i == pos) cout << ">";
				else cout << " ";
			}
			cout << "] " << int(tempProgress * 100) << " %\r";
			cout.flush();
		}
	}
	progressLock.unlock();
}

void saveRaysMissed() {
	raysMissedLock.lock();
	num_rays_missed++;
	raysMissedLock.unlock();
}

int main() {
	std::clock_t start;
	float runtime;

	Vector3D cameraPosition(-100, 100, 500);
	Vector3D lookPosition(0, 10, 0);
	
	Vector3D lightPosition(-200, 500, 500);
	FloatRGB lightIntensity(0.8, 0.8, 0.8);

	Camera cam(cameraPosition, lookPosition, WIDTH, HEIGHT, SCALE);
	PointLight light(lightPosition, lightIntensity);

	//Original scene. Camera: 1200x1200 0.1
	/*Vector3D s1(0, 0, -60);
	Vector3D s2(20, 0, 30);
	Vector3D s3(0, 40, 50);
	objects.push_back(new Sphere(s1, 40, FloatRGB(0.25, 0.125, 0), FloatRGB(1, 0.5, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(s2, 20, FloatRGB(0, 0.25, 0), FloatRGB(0, 1, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Sphere(s3, 15, FloatRGB(0, 0, 0.25), FloatRGB(0, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(Vector3D(20, 0, 50), Vector3D(0, 0, 50), Vector3D(0, 40, 50), FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));*/

	//Dodecahedron object. Camera: 1200x1200 0.004
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
	objects.push_back(new Triangle3D(v14, v7, v2, FloatRGB(0.25, 0, 0.25), FloatRGB(1, 0, 1), FloatRGB(0.5, 0.5, 0.5)));
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


	//Diamond object. Camera: 1200x1200 0.04
	/*Vector3D v1(10, 0, -10); Vector3D v2(10, 0, 10);
	Vector3D v3(-10, 0, -10); Vector3D v4(-10, 0, 10);
	Vector3D v5(0, 20, 0); Vector3D v6(0, -20, 0);

	objects.push_back(new Triangle3D(v1, v2, v5, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v2, v6, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v2, v4, v5, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v6, v4, v2, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v3, v4, v5, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v3, v4, v6, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v3, v5, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));
	objects.push_back(new Triangle3D(v1, v3, v6, FloatRGB(0.25, 0, 0), FloatRGB(1, 0, 0), FloatRGB(0.5, 0.5, 0.5)));*/

	cout << cam.toString() << endl;
	/*for (Object3D* obj : objects) {
		cout << obj->toString() << endl;
	}*/

	PLYReader plyReader("bun_zipper.ply");
	plyReader.readPLY(objects, vertices);

	image.resize(WIDTH * HEIGHT * 3);

	cout << std::fixed << std::setprecision(2);

	start = std::clock();

	#pragma omp parallel for
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			Vector3D tempPoint;
			Vector3D tempNormal;
			Vector3D hitPoint;
			Vector3D hitNormal;
			float distance;
			float tempDistance = INT32_MAX;
			FloatRGB colour;
			Object3D* hitObject = objects[0];

			bool hit = false;
			for (Object3D* obj : objects) {
				if (obj->intersect(objects, cam.getPixelPosition(i, j), cam.getVPN(), tempPoint, tempNormal, distance, light)) {
					if (distance < tempDistance) {
						hit = true;
						tempDistance = distance;
						hitObject = obj;
						hitPoint = tempPoint;
						hitNormal = tempNormal;
					}
				}
			}
			if (hit) {
				colour = hitObject->getColourValue(objects, hitPoint, hitNormal, light, cam.getPixelPosition(i, j));
			}
			else {
				colour = backgroundColour;
				saveRaysMissed();
			}
			savePixel(image, i, j, colour);

			maxValue = colour.r > maxValue ? colour.r : maxValue;
			maxValue = colour.g > maxValue ? colour.g : maxValue;
			maxValue = colour.b > maxValue ? colour.b : maxValue;
			minValue = colour.r < minValue ? colour.r : minValue;
			minValue = colour.g < minValue ? colour.g : minValue;
			minValue = colour.b < minValue ? colour.b : minValue;
		}
		saveProgress(HEIGHT);
	}
	runtime = (std::clock() - start) / (float) CLOCKS_PER_SEC;

	cout << endl << "Finished in time: " << runtime << " seconds" << endl;

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

	int numTriangles = 0, numSpheres = 0;
	for (Object3D* obj : objects) {
		if (dynamic_cast<Triangle3D*>(obj)) numTriangles++;
		if (dynamic_cast<Sphere*>(obj)) numSpheres++;
		delete obj;
	}
	cout << "\rDone!             " << endl;
	cout << "Rendered: " << numTriangles << " triangle | " << numSpheres << " sphere";

	Logger log(LOG_FILENAME);
	log.createEntry(HEIGHT, WIDTH, runtime, numTriangles, numSpheres, num_rays_missed);

	return 0;
}

