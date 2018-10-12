#ifndef Vector3D_H
#define Vector3D_H

#include <string>

class Vector3D
{
    public:
        Vector3D();
        Vector3D(int x, int y, int z);
        Vector3D(const int a [3], const int b [3]);
        virtual ~Vector3D();

        int getX() const;
        int getY() const;
        int getZ() const;
        void setX(int x);
        void setY(int y);
        void setZ(int z);

        double magnitude() const;
        double cosTheta(const Vector3D& v);

        Vector3D operator+ (const Vector3D& v);
        Vector3D operator- (const Vector3D& v);
        Vector3D operator* (const int k);
        Vector3D operator/ (const int k);

        std::string toString();
    protected:

    private:
        int x;
        int y;
        int z;

        double dotP(const Vector3D& v);
};

#endif // VECTOR_H
