#ifndef TRIANGLE_H
#define TRIANGLE_H
class Triangle3D : public Object3D {
	public:
		Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC);
		Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Triangle3D();

		bool intersect(Vector3D rayOrigin, Vector3D directionVector);
		bool intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance,
			PointLight& light, FloatRGB& colour);
		Vector3D getNormal(Vector3D point);

		std::string toString();
	protected:

	private:
		Vector3D pointA;
		Vector3D pointB;
		Vector3D pointC;

		FloatRGB getColourValue(std::vector<Object3D*>& objects, Vector3D point, PointLight& light, Vector3D rayOrigin);
};
#endif // TRIANGLE_H
