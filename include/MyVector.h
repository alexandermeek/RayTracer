#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <string>

class MyVector
{
    public:
        MyVector();
        MyVector(int x, int y, int z);
        MyVector(const int a [3], const int b [3]);
        virtual ~MyVector();

        int getX() const;
        int getY() const;
        int getZ() const;
        void setX(int x);
        void setY(int y);
        void setZ(int z);

        double magnitude() const;
        double cosTheta(const MyVector& v);

        MyVector operator+ (const MyVector& v);
        MyVector operator- (const MyVector& v);
        MyVector operator* (const int k);
        MyVector operator/ (const int k);

        std::string toString();
    protected:

    private:
        int x;
        int y;
        int z;

        double dotP(const MyVector& v);
};

#endif // VECTOR_H
