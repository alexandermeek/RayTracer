#include "pch.h"
#include "KDNode.h"

#include <limits>
#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::vector;
using std::endl;

KDNode::KDNode(const int maxDepth) : maxDepth(maxDepth) {}

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

int KDNode::count_leaves() const {
	int total = 0;
	if (left == nullptr) {
		total++;
	}
	else {
		total += left->count_leaves();
	}
	if (right == nullptr) {
		total++;
	}
	else {
		total += right->count_leaves();
	}

	return total;
}

BoundingBox KDNode::surround_with_box(const std::vector<Object3D*>& objects) {
	Vector3D vmax(INT32_MIN, INT32_MIN, INT32_MIN);
	Vector3D vmin(INT32_MAX, INT32_MAX, INT32_MAX);

	for (Object3D* obj : objects) {
		BoundingBox oBox = obj->getBoundingBox();
		if (oBox.vmax.x > vmax.x) vmax.x = oBox.vmax.x;
		if (oBox.vmax.y > vmax.y) vmax.y = oBox.vmax.y;
		if (oBox.vmax.z > vmax.z) vmax.z = oBox.vmax.z;
		if (oBox.vmin.x < vmin.x) vmin.x = oBox.vmin.x;
		if (oBox.vmin.y < vmin.y) vmin.y = oBox.vmin.y;
		if (oBox.vmin.z < vmin.z) vmin.z = oBox.vmin.z;
	}
	
	return BoundingBox(vmin, vmax);
}

KDNode* KDNode::build(const vector<Object3D*>& objects, const BoundingBox bBox, const int depth) {
	KDNode* node = new KDNode(maxDepth);
	node->left = nullptr;
	node->right = nullptr;
	node->bBox = bBox;
	
	if (depth >= maxDepth) {
		node->objects = objects;
		return node;
	}

	if (objects.size() <= 5) {
		node->objects = objects;
		return node;
	}

	vector<Object3D*> leftObjects, rightObjects;
	BoundingBox leftBBox, rightBBox;

	int axis = bBox.getLongestAxis();
	Vector3D bCentre = bBox.getCentre();

	switch (axis) {
	case BoundingBox::AXIS_X:
		leftBBox.vmin = bBox.vmin;
		leftBBox.vmax = Vector3D(bCentre.x, bBox.vmax.y, bBox.vmax.z);
		rightBBox.vmin = Vector3D(bCentre.x, bBox.vmin.y, bBox.vmin.z);
		rightBBox.vmax = bBox.vmax;
		break;
	case BoundingBox::AXIS_Y:
		leftBBox.vmin = bBox.vmin;
		leftBBox.vmax = Vector3D(bBox.vmax.x, bCentre.y, bBox.vmax.z);
		rightBBox.vmin = Vector3D(bBox.vmin.x, bCentre.y, bBox.vmin.z);
		rightBBox.vmax = bBox.vmax;
		break;
	case BoundingBox::AXIS_Z:
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

bool KDNode::intersect(const KDNode* node, Ray ray, Object3D** hitObject, Vector3D& point, 
	Vector3D& normal, float& distance, float& origin_offset) const {
	//Will only be run at root node.
	if (node->bBox.contains(ray.origin)) {
		switch (node->bBox.getLongestAxis()) {
		case BoundingBox::AXIS_X:
			origin_offset = abs(node->bBox.vmax.x - node->bBox.vmin.x);
			break;
		case BoundingBox::AXIS_Y:
			origin_offset = abs(node->bBox.vmax.y - node->bBox.vmin.y);
			break;
		case BoundingBox::AXIS_Z:
			origin_offset = abs(node->bBox.vmax.z - node->bBox.vmin.z);
			break;
		}
		ray.direction = ray.direction;
		Vector3D temp = ray.origin;
		ray.origin = ray.origin - (ray.direction * origin_offset * 2);
		origin_offset = (temp - ray.origin).magnitude();
	}

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
					if (hitDistance < distance && hitDistance > origin_offset) {
						*hitObject = obj;
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
		if (!leftNull) leftHit = intersect(node->left, ray, hitObject, point, normal, distance, origin_offset);
		if (!leftHit) {
			if (!rightNull) rightHit = intersect(node->right, ray, hitObject, point, normal, distance, origin_offset);
			if (!rightHit) return false;
		}
	}
	else {
		if (!rightNull) rightHit = intersect(node->right, ray, hitObject, point, normal, distance, origin_offset);
		if (!rightHit) {
			if (!leftNull) leftHit = intersect(node->left, ray, hitObject, point, normal, distance, origin_offset);
			if (!leftHit) return false;
		}
	}

	return true;
}

std::string KDNode::toString(int depth) const {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "KDNode " << depth << ": {" << endl;
	for (int i = 0; i < depth; i++) stream << "   ";
	stream << "   NumOfTriangles " << objects.size() << endl;
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
