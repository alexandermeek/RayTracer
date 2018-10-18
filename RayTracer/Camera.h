#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    public:
        Camera();
        Camera(Vector3D vRP, Vector3D pRef, int width, int height);
        virtual ~Camera();
		
		Vector3D getVRP() const;
		Vector3D getVPN() const;
		Vector3D getVUV() const;
		Vector3D getVRV() const;
		void setVRP(Vector3D p);
		void setVPN(Vector3D v);
		void setVUV(Vector3D v);
		void setVRV(Vector3D v);
		Vector3D* getPixels();

		std::string toString();
    protected:

    private:
		Vector3D viewReferencePoint;
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
		int width;
		int height;
		Vector3D *pixels;

		void computePixels();
		Vector3D getPointUp(Vector3D p, double k);
		Vector3D getPointRight(Vector3D p, double k);
};

#endif // CAMERA_H
