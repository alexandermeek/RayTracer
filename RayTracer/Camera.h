#ifndef CAMERA_H
#define CAMERA_H
#include "Vector3D.h"


class Camera
{
    public:
        Camera();
        Camera(int pos [3]);
        virtual ~Camera();

    protected:

    private:
        int viewReferencePoint [3];
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
};

#endif // CAMERA_H
