#ifndef BOX_H
#define BOX_H
class Box : public Object3D {
	public:
		static const int AXISX = 0;
		static const int AXISY = 1;
		static const int AXISZ = 2;
		Vector3D vmin;
		Vector3D vmax;

		Box();
		Box(const Box &box);
		Box(Vector3D vmin, Vector3D vmax);
		Box(Vector3D vmin, Vector3D vmax, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Box();

		bool intersect(const Ray ray);
		bool intersect(const Ray ray, Vector3D& point, Vector3D& normal, float& distance);
		Vector3D getNormal(Vector3D point);

		Vector3D getCentre();
		int getLongestAxis();

		static Box getBoundingBox(std::vector<Triangle3D*> triangles);

		bool contains(Triangle3D* triangle);
		bool contains(Vector3D point);

		Box operator=(const Box &box);

		std::string toString();
	private:
		bool intersect(const Ray ray, float& distance);

		static void checkPointBoundaries(Vector3D point, Vector3D &vmin, Vector3D &vmax);
};
#endif // BOX_H

