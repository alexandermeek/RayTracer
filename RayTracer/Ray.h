#ifndef RAY_H
#define RAY_H
class Ray {
	public:
		Ray();
		Ray(const Vector3D origin, const Vector3D direction);

		Vector3D origin;
		Vector3D direction;

		friend std::ostream& operator<<(std::ostream& os, const Ray& rhs);
};
#endif // RAY_H
