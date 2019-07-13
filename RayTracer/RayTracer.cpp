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

std::string MODEL_EXTENSION = ".ply";

Options opt("options.txt");

std::vector<unsigned short> image;
std::vector<Object3D*> objects;
std::vector<Vector3D*> vertices;

float maxValue;
float minValue = INT32_MAX;

std::mutex progressLock;
std::mutex raysMissedLock;
int progress = 0;
int old_bar = -1;
int num_rays_missed = 0;

//Save a colour value to a specified pixel.
void savePixel(std::vector<unsigned short>& image, int i, int j, FloatRGB colour) {
	image[3 * opt.image_width * j + 3 * i + 0] = colour.r;
	image[3 * opt.image_width * j + 3 * i + 1] = colour.g;
	image[3 * opt.image_width * j + 3 * i + 2] = colour.b;
}

//Adjust colour values to fit within the range 0-255.
void normaliseColours() {
	#pragma omp parallel for
	for (int j = 0; j < opt.image_height; j++) {
		for (int i = 0; i < opt.image_width; i++) {
			image[3 * opt.image_width * j + 3 * i + 0] = (image[3 * opt.image_width * j + 3 * i + 0] - minValue) / (maxValue - minValue) * 255.0f;
			image[3 * opt.image_width * j + 3 * i + 1] = (image[3 * opt.image_width * j + 3 * i + 1] - minValue) / (maxValue - minValue) * 255.0f;
			image[3 * opt.image_width * j + 3 * i + 2] = (image[3 * opt.image_width * j + 3 * i + 2] - minValue) / (maxValue - minValue) * 255.0f;
		}
	}
}

//Save progress of rendering the image.
void saveProgress(int max) {
	progressLock.lock();
	int barWidth = 50;

	progress++;
	float tempProgress = (float)progress / (float)opt.image_height;

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

//Keep track of the number of rays that hit nothing.
void saveRaysMissed() {
	raysMissedLock.lock();
	num_rays_missed++;
	raysMissedLock.unlock();
}

int main() {
	std::clock_t start;
	float readTime, buildTime, runtime;

	//Read model from ply file.
	PLYReader plyReader(opt.model_path + opt.model_filename + MODEL_EXTENSION);
	start = std::clock();
	plyReader.readPLY(objects, vertices);
	readTime = (std::clock() - start) / (float)CLOCKS_PER_SEC;
	cout << "File read in: " << readTime << " seconds" << endl;

	//Get outer bounding volume for the whole scene.
	BoundingBox bounding_box = KDNode::surround_with_box(objects);

	//Direction vector for use in the camera. 
	//Points towards centre of the whole scene.
	Vector3D lookPosition = bounding_box.getCentre();

	//Change object colours to that defined in the options.
	#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < (int)objects.size(); i++) {
		objects[i]->setKA(opt.kA);
		objects[i]->setKD(opt.kD);
		objects[i]->setKS(opt.kS);
	}

	//objects.erase(objects.begin(), objects.begin() + 20000);

	//Build kd-tree
	KDNode* kDNode = new KDNode(opt.kdtree_max_depth);
	start = std::clock();
	cout << "Building KDTree..." << endl;
	kDNode = kDNode->build(objects, bounding_box, 0);
	buildTime = (std::clock() - start) / (float)CLOCKS_PER_SEC;
	cout << "KDTree built in: " << buildTime << " seconds" << endl;
	int kdtree_leaves = kDNode->count_leaves();

	//Create camera and lights.
	Camera cam(opt.camera_position, lookPosition, opt.image_width, opt.image_height, opt.image_scale, opt.projection_type);
	PointLight light(opt.light_position, opt.light_intensity);

	cout << cam << endl;

	image.resize(opt.image_width * opt.image_height * 3);

	cout << std::fixed << std::setprecision(2);

	saveProgress(opt.image_height);

	start = std::clock();

	//Render image.
	#pragma omp parallel for schedule(dynamic)
	for (int j = 0; j < opt.image_height; j++) {
		for (int i = 0; i < opt.image_width; i++) {
			Vector3D* point = new Vector3D();
			Vector3D* normal = new Vector3D();
			float* distance = new float(INT32_MAX);
			float* origin_offset = new float(0);
			FloatRGB colour;
			Object3D* hitObject;
			Ray ray = cam.getRayAtPosition(i, j);
			bool hit = kDNode->intersect(kDNode, ray, &hitObject, *point, *normal, *distance, *origin_offset);
			
			if (hit) {
				colour = hitObject->getColourValue(kDNode, *point, *normal, light, ray, opt.shadows);
			}
			else {
				colour = opt.background_colour;
				saveRaysMissed();
			}
			delete point;
			delete normal;
			delete distance;
			delete origin_offset;
			savePixel(image, i, j, colour);

			maxValue = colour.r > maxValue ? colour.r : maxValue;
			maxValue = colour.g > maxValue ? colour.g : maxValue;
			maxValue = colour.b > maxValue ? colour.b : maxValue;
			minValue = colour.r < minValue ? colour.r : minValue;
			minValue = colour.g < minValue ? colour.g : minValue;
			minValue = colour.b < minValue ? colour.b : minValue;
		}
		saveProgress(opt.image_height);
	}
	runtime = (std::clock() - start) / (float) CLOCKS_PER_SEC;

	cout << endl << "Finished in time: " << runtime << " seconds" << endl;

	//Check if max colour value exceeded 255, if so normalise.
	if (maxValue > 255) {
		cout << "Normalising colours...";
		normaliseColours();
		cout << "\rColours normalised!   " << endl;
	} else {
		cout << "Not normalising colours." << endl;
	}

	//Write image data to png.
	cout << "Writing to file...        ";
	unsigned error = lodepng::encode(opt.image_filename, std::vector<unsigned char>(image.begin(), image.end()), 
		opt.image_width, opt.image_height, LodePNGColorType (LCT_RGB), unsigned (8));
	if (error) std::cout << endl << "encoder error " << error
		<< ": " << lodepng_error_text(error) << std::endl;

	//Clear memory and count objects rendered.
	int numTriangles = 0, numSpheres = 0, numBoxes = 0;
	for (Object3D* obj : objects) {
		if (dynamic_cast<Triangle3D*>(obj)) numTriangles++;
		if (dynamic_cast<Sphere*>(obj)) numSpheres++;
		if (dynamic_cast<Box*>(obj)) numBoxes++;
		delete obj;
	}
	for (Vector3D* vec : vertices) {
		delete vec;
	}

	cout << "\rDone!             " << endl;
	cout << "Rendered: " << numTriangles << " triangles | " << numSpheres << " spheres | "
		<< numBoxes << " boxes";

	//Add log entry.
	Logger log(opt.log_filename);
	log.createEntry(opt.image_height, opt.image_width, buildTime, runtime, numTriangles, numSpheres, numBoxes, num_rays_missed, opt.kdtree_max_depth, kdtree_leaves);
	
	return 0;
}

