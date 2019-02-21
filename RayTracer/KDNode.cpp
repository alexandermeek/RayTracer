#include "pch.h"
#include "KDNode.h"

#include <limits>
#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

//https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/

using std::vector;
using std::endl;

KDNode::KDNode(int maxDepth) {
	this->maxDepth = maxDepth;
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

BoundingBox KDNode::getBoundingBox() const {
	return bBox;
}

KDNode* KDNode::build(vector<Object3D*>& objects, BoundingBox bBox, int depth) {
	KDNode* node = new KDNode(maxDepth);
	node->objects = objects;
	node->left = nullptr;
	node->right = nullptr;
	node->bBox = bBox;
	
	if (depth >= maxDepth) return node;

	if (objects.size() <= 3) return node;

	vector<Object3D*> leftObjects, rightObjects;
	BoundingBox leftBBox, rightBBox;

	int axis = bBox.getLongestAxis();
	Vector3D bCentre = bBox.getCentre();

	switch (axis) {
	case Box::AXIS_X:
		leftBBox.vmin = bBox.vmin;
		leftBBox.vmax = Vector3D(bCentre.x, bBox.vmax.y, bBox.vmax.z);
		rightBBox.vmin = Vector3D(bCentre.x, bBox.vmin.y, bBox.vmin.z);
		rightBBox.vmax = bBox.vmax;
		break;
	case Box::AXIS_Y:
		leftBBox.vmin = bBox.vmin;
		leftBBox.vmax = Vector3D(bBox.vmax.x, bCentre.y, bBox.vmax.z);
		rightBBox.vmin = Vector3D(bBox.vmin.x, bCentre.y, bBox.vmin.z);
		rightBBox.vmax = bBox.vmax;
		break;
	case Box::AXIS_Z:
		leftBBox.vmin = bBox.vmin;
		leftBBox.vmax = Vector3D(bBox.vmax.x, bBox.vmax.y, bCentre.z);
		rightBBox.vmin = Vector3D(bBox.vmin.x, bBox.vmin.y, bCentre.z);
		rightBBox.vmax = bBox.vmax;
		break;
	}

	for (Object3D* obj : objects) {
		BoundingBox oBox = obj->getBoundingBox();
		if (oBox.overlaps(leftBBox)) leftObjects.push_back(obj);
		if (oBox.overlaps(rightBBox)) rightObjects.push_back(obj);
	}

	if (leftObjects.size() > 0) {
		node->left = build(leftObjects, leftBBox, depth + 1);
	}
	if (rightObjects.size() > 0) {
		node->right = build(rightObjects, rightBBox, depth + 1);
	}

	return node;
}

bool KDNode::intersect(KDNode* node, const Ray ray, Object3D* hitObject, Vector3D& point, 
	Vector3D& normal, float& distance) {
	float t;
	if (!node->bBox.intersect(ray, t)) return false;

	bool leftNull = node->left == nullptr;
	bool rightNull = node->right == nullptr;

	if (leftNull && rightNull) {
		float hitDistance;
		Vector3D hitPoint, hitNormal;
		bool hit = false;
		for (Object3D* obj : node->objects) {
			if (obj->intersect(ray, hitPoint, hitNormal, hitDistance)) {
				if (bBox.contains(hitPoint)) {
					if (hitDistance < distance) {
						hitObject = obj;
						point = hitPoint;
						normal = hitNormal;
						distance = hitDistance;
						hit = true;
					}
				}
			}
		}
		return hit;
	}

	bool leftHit = false, rightHit = false;
	float leftDistance = INT32_MAX, rightDistance = INT32_MAX;

	if (!leftNull) leftHit = node->left->bBox.intersect(ray, leftDistance);
	if (!rightNull) rightHit = node->right->bBox.intersect(ray, rightDistance);
	if (!leftHit && !rightHit) return false;

	if (leftDistance <= rightDistance) {
		if (!leftNull) leftHit = intersect(node->left, ray, hitObject, point, normal, distance);
		if (!leftHit) {
			if (!rightNull) rightHit = intersect(node->right, ray, hitObject, point, normal, distance);
			if (!rightHit) return false;
		}
	}
	else {
		if (!rightNull) rightHit = intersect(node->right, ray, hitObject, point, normal, distance);
		if (!rightHit) {
			if (!leftNull) leftHit = intersect(node->left, ray, hitObject, point, normal, distance);
			if (!leftHit) return false;
		}
	}

	return true;
}

std::string KDNode::toString(int depth) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "KDNode " << depth << ": {" << endl;
	for (int i = 0; i < depth; i++) stream << "   ";
	stream << "   NumOfTriangles " << objects.size() << endl;
	for (int i = 0; i < depth; i++) stream << "   ";
	stream << "   " << bBox.toString() << endl;
	depth++;
	if (left != nullptr) {
		stream << endl;
		for (int i = 0; i < depth; i++) stream << "   ";
		stream << "Left " << left->toString(depth);
	}
	if (right != nullptr) {
		stream << endl;
		for (int i = 0; i < depth; i++) stream << "   ";
		stream << "Right " << right->toString(depth);
	}
	for (int i = 0; i < depth - 1; i++) stream << "   ";
	stream	<< "}" << endl;
	return stream.str();
}
