#ifndef BOX_H
#define BOX_H
class Box : public Object3D {
	public:
		Box(Vector3D vmin, Vector3D vmax);
		Box(Vector3D vmin, Vector3D vmax, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Box();

		bool intersect(Vector3D rayOrigin, Vector3D directionVector);
		bool intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, Vector3D& normal,
			float& distance);
		Vector3D getNormal(Vector3D point);

		std::string toString();
	private:
		Vector3D vmin;
		Vector3D vmax;
		Vector3D getCentre();
};
#endif // BOX_H

