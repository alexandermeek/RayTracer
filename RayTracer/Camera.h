#ifndef CAMERA_H
#define CAMERA_H
#include "Vector3D.h"


class Camera {
    public:
        Camera();
        Camera(double pos [3], double lookPos [3]);
        virtual ~Camera();

		//double [] getViewReferencePoint() const;
    protected:

    private:
        double viewReferencePoint [3];
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
};

#endif // CAMERA_H
