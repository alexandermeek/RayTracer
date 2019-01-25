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

const std::string MODEL_PATH = "models/";
const std::string FILENAME = "render.png";
const std::string LOG_FILENAME = "log.txt";

//To keep the same composition in frame if you multiply the width by X, divide the scale by X.
const int WIDTH = 100; //Width of image.
const int HEIGHT = 100; //Height of image.
const float SCALE = 0.35; //Scale of the image.
const int PROJECTION_TYPE = Camera::PERSPECTIVE; //Projection type of the image.
const FloatRGB BACKGROUND_COLOUR(30, 30, 30); //Background colour of the scene.

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

	Vector3D cameraPosition(0, 0, 100);
	Vector3D lookPosition(0, 0, 0);
	
	Vector3D lightPosition(200, 300, 500);
	FloatRGB lightIntensity(0.8, 0.8, 0.8);

	Camera cam(cameraPosition, lookPosition, WIDTH, HEIGHT, SCALE, PROJECTION_TYPE);
	PointLight light(lightPosition, lightIntensity);
	
	cout << cam.toString() << endl;

	//Original scene	Camera: 1200x1200 0.1	File: original_scene.ply
	//Diamond			Camera: 1200x1200 0.04	File: diamond.ply
	//Dodecahedron		Camera: 1200x1200 0.4	File: dodecahedron.ply
	//Bunny				Camera: 100x100 0.24	File: bun_zipper.ply or bun_zipper_res4.ply

	PLYReader plyReader(MODEL_PATH + "original_scene.ply");
	plyReader.readPLY(objects, vertices);

	//objects.push_back(new Box(Vector3D(-10, -10, -10), Vector3D(10, 10, 10)));
	//objects.push_back(new Sphere(Vector3D(0, 0, 0), 15));

	//Here you can set/override the colour of all triangles in the scene.
	//Some models used don't come with colours, so will default to greyscale.
	FloatRGB kA(0.25, 0, 0);
	FloatRGB kD(0.25, 0, 0);
	FloatRGB kS(0.5, 0.5, 0.5);
	for (Object3D* obj : objects) {
		obj->setKA(kA);
		obj->setKD(kD);
		obj->setKS(kS);
	}

	image.resize(WIDTH * HEIGHT * 3);

	cout << std::fixed << std::setprecision(2);

	saveProgress(HEIGHT);

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
				if (obj->intersect(cam.getRayAtPosition(i, j), tempPoint, tempNormal, distance)) {
					hit = true;
					if (distance < tempDistance) {
						tempDistance = distance;
						hitObject = obj;
						hitPoint = tempPoint;
						hitNormal = tempNormal;
					}
				}
			}
			if (hit) {
				colour = hitObject->getColourValue(objects, hitPoint, hitNormal, light, cam.getRayAtPosition(i, j));
			}
			else {
				colour = BACKGROUND_COLOUR;
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

	int numTriangles = 0, numSpheres = 0, numBoxes = 0;
	for (Object3D* obj : objects) {
		if (dynamic_cast<Triangle3D*>(obj)) numTriangles++;
		if (dynamic_cast<Sphere*>(obj)) numSpheres++;
		if (dynamic_cast<Box*>(obj)) numBoxes++;
		delete obj;
	}
	cout << "\rDone!             " << endl;
	cout << "Rendered: " << numTriangles << " triangles | " << numSpheres << " spheres | "
		<< numBoxes << " boxes";

	Logger log(LOG_FILENAME);
	log.createEntry(HEIGHT, WIDTH, runtime, numTriangles, numSpheres, numBoxes, num_rays_missed);

	return 0;
}

