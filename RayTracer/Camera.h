#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    public:
		enum PROJECTION_TYPE {ORTHOGRAPHIC, PERSPECTIVE};

        Camera();
        Camera(const Vector3D vRP, const Vector3D pRef, const int width, const int height, 
			const float scale, const int type);
        virtual ~Camera();
		
		int getWidth() const;
		int getHeight() const;
		Vector3D getVRP() const;
		Vector3D getVPN() const;
		Vector3D getVUV() const;
		Vector3D getVRV() const;
		Ray getRayAtPosition(const int x, const int y) const;

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
		Ray computeRay(const int x, const int y, const Vector3D topLeftPixel) const;
		Vector3D getPointDown(const Vector3D p, const float k) const;
		Vector3D getPointRight(const Vector3D p, const float k) const;
		Vector3D getPointForward(const Vector3D p, const float k) const;
};

#endif // CAMERA_H
