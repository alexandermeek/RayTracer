#ifndef TRIANGLE_H
#define TRIANGLE_H
class Triangle3D : public Object3D {
	public:
		Triangle3D(const Vector3D pointA, const Vector3D pointB, const Vector3D pointC);
		Triangle3D(const Vector3D pointA, const Vector3D pointB, const Vector3D pointC, 
			const FloatRGB kA, const FloatRGB kD, const FloatRGB kS);

		Vector3D getPointA() const;
		Vector3D getPointB() const;
		Vector3D getPointC() const;

		virtual bool intersect(Ray ray, float& distance) const;
		virtual bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) const;
		virtual Vector3D getNormal(Vector3D point) const;
		BoundingBox getBoundingBox() const;

		friend std::ostream& operator<<(std::ostream& os, const Triangle3D& rhs);
	protected:
		
	private:
		Vector3D pointA;
		Vector3D pointB;
		Vector3D pointC;
};
#endif // TRIANGLE_H
