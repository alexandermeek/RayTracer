#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <ostream>
#include <vector>
class KDNode;

class Object3D
{
	public:
		enum LIGHT_TYPE {UNIDIRECTIONAL, BIDIRECTIONAL};

		Object3D();
		Object3D(const FloatRGB kA, const FloatRGB kD, const FloatRGB kS, const int lightType);
		virtual ~Object3D();

		FloatRGB getKA() const;
		FloatRGB getKD() const;
		FloatRGB getKS() const;
		void setKA(const FloatRGB kA);
		void setKD(const FloatRGB kD);
		void setKS(const FloatRGB kS);

		virtual bool intersect(Ray ray, float& distance) const = 0;
		virtual bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) const = 0;
		virtual Vector3D getNormal(Vector3D point) const = 0;
		virtual BoundingBox getBoundingBox() const = 0;

		FloatRGB getColourValue(const KDNode* kDNode, Vector3D point, Vector3D normal, std::vector<LightSource*>& lights, Ray ray, bool shadows);

		friend std::ostream& operator<<(std::ostream& os, const Object3D& rhs);
	protected:
		const float EPSILON = 0.00001f;
		const float SHADOW_BIAS = 1e-4f;
	private:
		FloatRGB kA;
		FloatRGB kD;
		FloatRGB kS;
		int lightType;
};
#endif // OBJECT3D_H