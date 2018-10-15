#ifndef CAMERA_H
#define CAMERA_H

#include "Point3D.h"

class Camera {
    public:
        Camera();
        Camera(Point3D vRP, Point3D pRef, int width, int height);
        virtual ~Camera();
		
		Point3D getVRP() const;
		Vector3D getVPN() const;
		Vector3D getVUV() const;
		Vector3D getVRV() const;
		void setVRP(Point3D p);
		void setVPN(Vector3D v);
		void setVUV(Vector3D v);
		void setVRV(Vector3D v);
		Point3D* getPixels();

		std::string toString();
    protected:

    private:
        Point3D viewReferencePoint;
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
		int width;
		int height;
		Point3D *pixels;

		void computePixels();
		Point3D getPointUp(Point3D p, double k);
		Point3D getPointRight(Point3D p, double k);
};

#endif // CAMERA_H
