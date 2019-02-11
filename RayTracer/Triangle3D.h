#ifndef TRIANGLE_H
#define TRIANGLE_H
class Triangle3D : public Object3D {
	public:
		Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC);
		Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Triangle3D();

		bool intersect(Ray ray);
		bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance);
		Vector3D getNormal(Vector3D point);

		std::string toString();
	protected:
		
	private:
		Vector3D pointA;
		Vector3D pointB;
		Vector3D pointC;

		bool intersect(Ray ray, float& distance);
};
#endif // TRIANGLE_H
