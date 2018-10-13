#ifndef POINT3D_H
#define POINT3D_H
#include <string>

class Point3D {
	public:
		Point3D(double x, double y, double z);
		~Point3D();

		double getX() const;
		double getY() const;
		double getZ() const;
		void setX(double x);
		void setY(double y);
		void setZ(double z);

		Vector3D operator- (const Point3D& p);

		std::string toString();

	protected:

	private:
		double x;
		double y;
		double z;
};

#endif // VECTOR_H