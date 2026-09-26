#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3D<float> Pos, Vector3D<float> Vel);
	~Particle();

	void integrateEuler(double t);
	void integrateEulerSemi(double t);
	void integrateVerlet(double t);

private:
	Vector3D<float> vel;
	physx::PxTransform pos;
	physx::PxTransform antPos;

	Vector3D<float> a = { 0.0f, 9.8f, 0.0f };

	float d = 0.7f;
	RenderItem* renderItem;
};