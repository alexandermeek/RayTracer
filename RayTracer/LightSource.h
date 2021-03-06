#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

class KDNode;
class LightSource{
    public:
        LightSource(const Vector3D position, const FloatRGB intensity);
        virtual ~LightSource();

        virtual float calculateShadow(const KDNode* kDNode, Vector3D point, 
            float& origin_offset) const = 0;

        Vector3D position;
        FloatRGB intensity;
};
#endif // LIGHTSOURCE_H