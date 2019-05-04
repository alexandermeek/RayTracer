#ifndef KDNODE_H
#define KDNODE_H
class KDNode {
	public:
		KDNode(int maxDepth);
		~KDNode();

		KDNode* getLeft() const;
		KDNode* getRight() const;
		BoundingBox getBoundingBox() const;

		int count_leaves() const;

		KDNode* build(std::vector<Object3D*>& objects, BoundingBox bBox, int depth);
		bool intersect(KDNode* node, Ray ray, Object3D** hitObject, Vector3D& point, 
			Vector3D& normal, float& distance, float& origin_offset);

		std::string toString(int depth); 
	private:
		int maxDepth;

		BoundingBox bBox;
		KDNode* left;
		KDNode* right;

		std::vector<Object3D*> objects;
};
#endif //KDNODE_H

