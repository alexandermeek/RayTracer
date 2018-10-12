#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
    public:
        Camera();
        virtual ~Camera();

    protected:

    private:
        int viewReferencePoint [3];
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
