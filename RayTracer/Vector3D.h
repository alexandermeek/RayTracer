#ifndef Vector3D_H
#define Vector3D_H

#include <string>

class Vector3D {
    public:
        Vector3D();
        Vector3D(double x, double y, double z);
        Vector3D(const double a [3], const double b [3]);
        virtual ~Vector3D();

        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double x);
        void setY(double y);
        void setZ(double z);

        double magnitude() const;
        double cosTheta(const Vector3D& v);

        Vector3D operator+ (const Vector3D& v);
        Vector3D operator- (const Vector3D& v);
        Vector3D operator* (const double k);
        Vector3D operator/ (const double k);

        std::string toString();
    protected:

    private:
        double x;
        double y;
        double z;

        double dotP(const Vector3D& v);
};

#endif // VECTOR_H
