#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle {
protected:
	Vector3D<float> vel;

	physx::PxTransform pos;
	physx::PxTransform antPos;

	Vector3D<float> a;

	float d = 0.7f;
	bool firstMove = true;

	RenderItem* renderItem;
public:
	Particle(Vector3D<float> Pos, Vector3D<float> Vel, Vector3D<float> ac = { 0.0f, -9.8f, 0.0f });
	virtual ~Particle();

	void integrateEuler(double t);
	void integrateEulerSemi(double t);
	void integrateVerlet(double t);

protected:
};