#include "pch.h"
#include "Camera.h"

Camera::Camera() {
    //ctor
}

Camera::Camera(double pos[3], double lookPos[3]) {
	for (int i = 0; i < 3; i++) {
		viewReferencePoint[i] = pos[i];
	}
}

Camera::~Camera() {
    //dtor
}
