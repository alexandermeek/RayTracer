#pragma once
class BoundingBox {
	public:
		BoundingBox();
		BoundingBox(Vector3D vmin, Vector3D vmax);
		~BoundingBox();

		Vector3D vmin;
		Vector3D vmax;

		const enum AXIS { AXIS_X, AXIS_Y, AXIS_Z };

		bool intersect(const Ray ray, float& distance);
		bool overlaps(const BoundingBox bBox);
		bool contains(const Vector3D point);

		Vector3D getCentre();
		int getLongestAxis();

		std::string toString() const;
};

