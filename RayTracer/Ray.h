#ifndef RAY_H
#define RAY_H
class Ray {
	public:
		Ray();
		Ray(Vector3D origin, Vector3D direction);
		~Ray();

		Vector3D origin;
		Vector3D direction;
};
#endif // RAY_H
