#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    public:
		const enum PROJECTION_TYPE {ORTHOGRAPHIC, PERSPECTIVE};

        Camera();
        Camera(Vector3D vRP, Vector3D pRef, int width, int height, float scale, int type);
        virtual ~Camera();
		
		int getWidth() const;
		int getHeight() const;
		Vector3D getVRP() const;
		Vector3D getVPN() const;
		Vector3D getVUV() const;
		Vector3D getVRV() const;
		Ray getRayAtPosition(int x, int y);

		friend std::ostream& operator<<(std::ostream& os, const Camera& rhs);
    protected:

    private:
		Vector3D viewReferencePoint;
        Vector3D viewPlaneNormalVector;
        Vector3D viewUpVector;
        Vector3D viewRightVector;
		int width;
		int height;
		int meanSize;
		float scale;
		int type;
		Ray* rays;

		void computeRays();
		Ray computeRay(int x, int y, Vector3D topLeftPixel);
		Vector3D getPointDown(Vector3D p, float k);
		Vector3D getPointRight(Vector3D p, float k);
		Vector3D getPointForward(Vector3D p, float k);
};

#endif // CAMERA_H
