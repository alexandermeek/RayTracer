#ifndef KDNODE_H
#define KDNODE_H

#include <vector>
class KDNode {
	public:
		KDNode(const int maxDepth);
		~KDNode();

		KDNode* getLeft() const;
		KDNode* getRight() const;
		BoundingBox getBoundingBox() const;

		int count_leaves() const;
		
		static BoundingBox surround_with_box(const std::vector<Object3D*>& objects);
		KDNode* build(const std::vector<Object3D*>& objects, const BoundingBox bBox, const int depth);
		bool intersect(const KDNode* node, Ray ray, Object3D** hitObject, Vector3D& point, 
			Vector3D& normal, float& distance, float& origin_offset) const;

		std::string toString(int depth) const; 
	private:
		int maxDepth;

		BoundingBox bBox;
		KDNode* left;
		KDNode* right;

		std::vector<Object3D*> objects;
};
#endif //KDNODE_H

