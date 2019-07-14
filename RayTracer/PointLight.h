#ifndef POINTLIGHT_H
#define POINTLIGHT_H

class PointLight : public LightSource {
	public:
		PointLight(Vector3D position, FloatRGB intensity);

		float calculateShadow(KDNode* kDNode, Vector3D point, 
			float& origin_offset) const;

		friend std::ostream& operator<<(std::ostream& os, const PointLight& rhs);
};
#endif // POINTLIGHT_H

