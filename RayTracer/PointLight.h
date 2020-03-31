#ifndef POINTLIGHT_H
#define POINTLIGHT_H

class PointLight : public LightSource {
	public:
		PointLight(const Vector3D position, const FloatRGB intensity);

		float calculateShadow(const KDNode* kDNode, Vector3D point, 
			float& origin_offset) const;

		friend std::ostream& operator<<(std::ostream& os, const PointLight& rhs);
};
#endif // POINTLIGHT_H

