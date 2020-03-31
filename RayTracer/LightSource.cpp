#include "pch.h"
#include "LightSource.h"

LightSource::LightSource(const Vector3D position, const FloatRGB intensity) 
    : position(position), intensity(intensity) {}

LightSource::~LightSource() {}