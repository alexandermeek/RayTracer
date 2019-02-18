#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>

class Object3D
{
	public:
		static const bool BIDIRECTIONAL = true;
		static const bool UNIDIRECTIONAL = false;

		Object3D();
		Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS, bool useBidirectionalLight);
		~Object3D();

		FloatRGB getKA() const;
		FloatRGB getKD() const;
		FloatRGB getKS() const;
		void setKA(FloatRGB kA);
		void setKD(FloatRGB kD);
		void setKS(FloatRGB kS);

		virtual bool intersect(Ray ray);
		virtual bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance);
		virtual Vector3D getNormal(Vector3D point);

		FloatRGB getColourValue(std::vector<Object3D*>& objects, Vector3D point, Vector3D normal, PointLight light, Ray ray);

		virtual std::string toString(); 
	protected:
		const float EPSILON = 0.00001;
	private:
		FloatRGB kA;
		FloatRGB kD;
		FloatRGB kS;
		bool useBidirectionalLight;

		virtual bool intersect(Ray ray, float& distance);
};
#endif // OBJECT3D_H