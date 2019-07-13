#include "pch.h"
#include "PLYReader.h"

#include <fstream>
#include <iostream>

PLYReader::PLYReader(std::string filename) : filename(filename) {}

std::string PLYReader::getFilename() {
	return filename;
}

int PLYReader::getNumVertices() {
	return numVertices;
}

int PLYReader::getNumFaces() {
	return numFaces;
}

bool PLYReader::readPLY(std::vector<Object3D*>& objects, std::vector<Vector3D*>& vertices) {
	std::string line;
	std::ifstream plyFile(filename);
	int fileStage = 0;

	if (!plyFile.is_open()) {
		return false;
	} else {
		while (std::getline(plyFile, line)) {
			switch (fileStage) {
			case 0 :
				if (line.substr(0, DESC_PLY.length()) == DESC_PLY) {
					std::cout << std::endl << "Reading a ply file: ";
					fileStage = 1;
				} 
				else {
					return false;
				}
				break;
			case 1 :
				if (line.substr(0, DESC_VERTICES.length()) == DESC_VERTICES) {
					numVertices = std::stoi(line.substr(DESC_VERTICES.length(), line.length()));
					std::cout << numVertices << " vertices | ";
				} 
				else {
					if (line.substr(0, DESC_FACES.length()) == DESC_FACES) {
						numFaces = std::stoi(line.substr(DESC_FACES.length(), line.length()));
						std::cout << numFaces << " faces";
					}
					else {
						if (line.substr(0, DESC_END_HEADER.length()) == DESC_END_HEADER) {
							fileStage = 2;
						}
					}
				}
				break;
			case 2 :
				if (line.substr(0, 2) == "3 ") {
					fileStage = 3;
					objects.push_back(new Triangle3D(readTriangle(line, vertices)));
				}
				else if (line.substr(0, 2) == "2 ") {
					fileStage = 3;
					objects.push_back(new Box(readBox(line, vertices)));
				}
				else if (line.substr(0, 2) == "1 ") {
					fileStage = 3;
					objects.push_back(new Sphere(readSphere(line, vertices)));
				}
				else {
					vertices.push_back(readPoint(line));
				}
				break;
			case 3 :
				if (line.substr(0, 2) == "3 ") {
					objects.push_back(new Triangle3D(readTriangle(line, vertices)));
				}
				else if (line.substr(0, 2) == "2 ") {
					objects.push_back(new Box(readBox(line, vertices)));
				}
				else {
					objects.push_back(new Sphere(readSphere(line, vertices)));
				}
				break;
			}
		}
		plyFile.close();
	}
	std::cout << std::endl << "File read!" << std::endl;
	return true;
}

Vector3D* PLYReader::readPoint(std::string line) {
	float v[3];
	int pos = 0;
	std::string token;

	for (int i = 0; i < 3; i++) {
		pos = line.find(DELIMITER);
		token = line.substr(0, pos);
		v[i] = std::stof(token) * 100.0f;
		line.erase(0, pos + DELIMITER.length());
	}

	Vector3D* vertex = new Vector3D(v[0], v[1], v[2]);
	return vertex;
}

Triangle3D PLYReader::readTriangle(std::string line, std::vector<Vector3D*>& vertices) {
	int v[3];
	int pos = 0;
	std::string token;

	line.erase(0, 2);

	for (int i = 0; i < 3; i++) {
		pos = line.find(DELIMITER);
		token = line.substr(0, pos);
		v[i] = std::stoi(token);
		line.erase(0, pos + DELIMITER.length());
	}

	Triangle3D tri(*vertices[v[0]], *vertices[v[1]], *vertices[v[2]]);
	return tri;
}

Sphere PLYReader::readSphere(std::string line, std::vector<Vector3D*>& vertices) {
	int centerV;
	float radius;
	int pos = 0;
	std::string token;

	line.erase(0, 2);

	pos = line.find(DELIMITER);
	token = line.substr(0, pos);
	centerV = std::stoi(token);
	line.erase(0, pos + DELIMITER.length());

	pos = line.find(DELIMITER);
	token = line.substr(0, pos);
	radius = std::stof(token);

	Sphere sph(*vertices[centerV], radius);
	return sph;
}

Box PLYReader::readBox(std::string line, std::vector<Vector3D*>& vertices) {
	int vmax, vmin;
	int pos = 0;
	std::string token;

	line.erase(0, 2);

	pos = line.find(DELIMITER);
	token = line.substr(0, pos);
	vmin = std::stoi(token);
	line.erase(0, pos + DELIMITER.length());

	pos = line.find(DELIMITER);
	token = line.substr(0, pos);
	vmax = std::stof(token);

	Box box(*vertices[vmin], *vertices[vmax]);
	return box;
}
