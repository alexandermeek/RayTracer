#ifndef CAMERA_H
#define CAMERA_H

#include "Point3D.h"

class Camera {
    public:
        Camera();
        Camera(Point3D vRP, Point3D pRef);
        virtual ~Camera();

    protected:

    private:
        Point3D viewReferencePoint;
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
};

#endif // CAMERA_H
