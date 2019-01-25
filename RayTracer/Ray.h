#ifndef RAY_H
#define RAY_H
class Ray {
	public:
		Ray();
		Ray(Vector3D origin, Vector3D direction);
		~Ray();

		Vector3D origin;
		Vector3D direction;

		std::string toString();
};
#endif // RAY_H
