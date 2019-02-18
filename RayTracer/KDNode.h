#ifndef KDNODE_H
#define KDNODE_H
class KDNode {
	public:
		KDNode();
		KDNode(std::vector<Triangle3D*> &triangles);
		~KDNode();

		KDNode* getLeft() const;
		KDNode* getRight() const;

		KDNode* build(std::vector<Triangle3D*>& triangles, int depth);
		bool intersect(KDNode* node, const Ray ray, Vector3D& point, Vector3D& normal, float& distance);

		std::string toString();
	private:
		Box bBox;
		KDNode* left;
		KDNode* right;

		std::vector<Triangle3D*> triangles;

		
};
#endif //KDNODE_H

