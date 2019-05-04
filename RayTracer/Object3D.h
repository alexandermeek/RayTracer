#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <ostream>
class KDNode;

class Object3D
{
	public:
		const enum LIGHT_TYPE {UNIDIRECTIONAL, BIDIRECTIONAL};

		Object3D();
		Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS, int lightType);
		~Object3D();

		FloatRGB getKA() const;
		FloatRGB getKD() const;
		FloatRGB getKS() const;
		void setKA(FloatRGB kA);
		void setKD(FloatRGB kD);
		void setKS(FloatRGB kS);

		virtual bool intersect(Ray ray, float& distance);
		virtual bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance);
		virtual Vector3D getNormal(Vector3D point);
		virtual BoundingBox getBoundingBox() const;

		FloatRGB getColourValue(KDNode* kDNode, Vector3D point, Vector3D normal, PointLight light, Ray ray, bool shadows);

		friend std::ostream& operator<<(std::ostream& os, const Object3D& rhs);
	protected:
		const float EPSILON = 0.00001f;
		const float SHADOW_BIAS = 1e-4;
	private:
		FloatRGB kA;
		FloatRGB kD;
		FloatRGB kS;
		int lightType;
};
#endif // OBJECT3D_H