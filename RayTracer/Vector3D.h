#ifndef Vector3D_H
#define Vector3D_H

#include <string>

class Vector3D {
    public:
        Vector3D();
        Vector3D(float x, float y, float z);
        virtual ~Vector3D();

		float magnitude() const;
		float cosTheta(const Vector3D& v) const;

		float dotProduct(const Vector3D& v) const;
		Vector3D crossProduct(const Vector3D& v) const;
		Vector3D unitVector() const;
		Vector3D inverse() const;

		Vector3D operator+ (const Vector3D& v) const;
        Vector3D operator- (const Vector3D& v) const;
        Vector3D operator* (const float k) const;
        Vector3D operator/ (const float k) const;
		Vector3D operator/ (const Vector3D& v) const;

		friend std::ostream& operator<<(std::ostream& os, const Vector3D& rhs);

		float x;
		float y;
		float z;
};

#endif // VECTOR_H
