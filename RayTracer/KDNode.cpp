#include "pch.h"
#include "KDNode.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

//https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/

using std::vector;
using std::endl;

KDNode::KDNode() {}

KDNode::KDNode(vector<Triangle3D*> &triangles) {
	this->triangles = triangles;
}

KDNode::~KDNode() {
	if (left != nullptr) {
		delete left;
	}
	if (right != nullptr) {
		delete right;
	}
}

KDNode* KDNode::getLeft() const {
	return left;
}

KDNode* KDNode::getRight() const {
	return right;
}

KDNode* KDNode::build(vector<Triangle3D*>& triangles, int depth) {
	KDNode* node = new KDNode();
	node->triangles = triangles;
	node->left = nullptr;
	node->right = nullptr;
	
	if (triangles.size() == 0) return node;

	if (triangles.size() == 1) {
		this->bBox = Box::getBoundingBox(triangles);
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->triangles = vector<Triangle3D*>();
		node->right->triangles = vector<Triangle3D*>();
		return node;
	}

	this->bBox = Box::getBoundingBox(triangles);

	vector<Triangle3D*> leftTriangles;
	vector<Triangle3D*> rightTriangles;

	int axis = bBox.getLongestAxis();
	Vector3D bCentre = bBox.getCentre();
	for (Triangle3D* tri : triangles) {
		Vector3D tCentre = tri->getCentre();
		switch (axis) {
			case Box::AXISX:
				bCentre.x >= tCentre.x ? rightTriangles.push_back(tri) : leftTriangles.push_back(tri);
				break;
			case Box::AXISY:
				bCentre.y >= tCentre.y ? rightTriangles.push_back(tri) : leftTriangles.push_back(tri);
				break;
			case Box::AXISZ:
				bCentre.z >= tCentre.z ? rightTriangles.push_back(tri) : leftTriangles.push_back(tri);
				break;
		}
	}

	if (leftTriangles.size() == 0 && rightTriangles.size() > 0) leftTriangles = rightTriangles;
	if (rightTriangles.size() == 0 && leftTriangles.size() > 0) rightTriangles = leftTriangles;

	int matches = 0;
	for (Triangle3D* triL : leftTriangles) {
		for (Triangle3D* triR : rightTriangles) {
			if (triL == triR) matches++;
		}
	}

	if ((float)matches / leftTriangles.size() < 0.5 && (float)matches / rightTriangles.size() < 0.5) {
		node->left = build(leftTriangles, depth + 1);
		node->right = build(rightTriangles, depth + 1);
	}
	else {
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->triangles = vector<Triangle3D*>();
		node->right->triangles = vector<Triangle3D*>();
	}

	return node;
}

bool KDNode::intersect(KDNode* node, const Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	if (!node->bBox.intersect(ray)) return false;

	Vector3D normal;
	Vector3D point;
	float distance;
	bool hitTriangle = false;

	if (node->left->triangles.size() > 0 || node->right->triangles.size() > 0) {
		bool hitLeft = node->left->bBox.intersect(ray, point, normal, distance);
		//todo; finish
	}
}

std::string KDNode::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "KDNode: {" << endl
		<< "   NumOfTriangles " << triangles.size() << endl << "}";
	return stream.str();
}
