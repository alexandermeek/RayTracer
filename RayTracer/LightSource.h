#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

class KDNode;
class LightSource{
    public:
        LightSource(FloatRGB intensity);
        virtual ~LightSource();

        virtual float calculateShadow(KDNode* kDNode, Vector3D point, 
            float& origin_offset) const = 0;

        FloatRGB intensity;
};
#endif // LIGHTSOURCE_H