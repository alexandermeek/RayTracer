#include "pch.h"
#include "LightSource.h"

LightSource::LightSource(Vector3D position, FloatRGB intensity) : position(position), intensity(intensity) {}

LightSource::~LightSource() {}