#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector();
        virtual ~Vector();

        int getX();
        int getY();
        int getZ();

        Vector operator+ (const Vector& v );
        Vector operator- (const Vector& v );
        Vector operator* (const Vector& v );
        Vector operator/ (const Vector& v );

    protected:

    private:
        int x;
        int y;
        int z;
};

#endif // VECTOR_H
