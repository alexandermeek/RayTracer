#ifndef Vector3D_H
#define Vector3D_H

#include <string>

class Vector3D {
    public:
        Vector3D();
        Vector3D(float x, float y, float z);
        virtual ~Vector3D();

		float getX() const;
		float getY() const;
		float getZ() const;
        void setX(float x);
        void setY(float y);
        void setZ(float z);

		float magnitude() const;
		float cosTheta(const Vector3D& v);

		float dotProduct(const Vector3D& v);
		Vector3D crossProduct(const Vector3D& v);
		Vector3D unitVector();

		Vector3D operator+ (const Vector3D& v);
        Vector3D operator- (const Vector3D& v);
        Vector3D operator* (const float k);
        Vector3D operator/ (const float k);
		Vector3D operator/ (const Vector3D& v);

        std::string toString();
    protected:

    private:
		float x;
		float y;
		float z;
};

#endif // VECTOR_H
