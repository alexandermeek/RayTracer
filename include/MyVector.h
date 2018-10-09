#ifndef MYVECTOR_H
#define MYVECTOR_H


class MyVector
{
    public:
        MyVector();
        MyVector(int x, int y, int z);
        virtual ~MyVector();

        double getLength();
        int getX() const;
        int getY() const;
        int getZ() const;
        void setX(int x);
        void setY(int y);
        void setZ(int z);

        MyVector operator+ (const MyVector& v);
        MyVector operator- (const MyVector& v);
        MyVector operator* (const MyVector& v);
        MyVector operator/ (const MyVector& v);

        int main();

    protected:

    private:
        int x;
        int y;
        int z;
};

#endif // VECTOR_H
