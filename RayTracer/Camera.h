#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    public:
        Camera();
        Camera(Vector3D vRP, Vector3D pRef, int width, int height);
        virtual ~Camera();
		
		int getWidth() const;
		int getHeight() const;
		Vector3D getVRP() const;
		Vector3D getVPN() const;
		Vector3D getVUV() const;
		Vector3D getVRV() const;
		void setWidth(int x);
		void setHeight(int y);
		void setVRP(Vector3D p);
		void setVPN(Vector3D v);
		void setVUV(Vector3D v);
		void setVRV(Vector3D v);
		Vector3D getPixelPosition(int x, int y);

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
		Vector3D computePixel(int x, int y, Vector3D topLeftPixel);
		Vector3D getPointDown(Vector3D p, float k);
		Vector3D getPointRight(Vector3D p, float k);
};

#endif // CAMERA_H
