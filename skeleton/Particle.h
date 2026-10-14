#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3D<float> Pos, Vector3D<float> Vel, Vector3D<float> ac = { 0.0f, -10.f, 0.0f }, float size = 1.f, Vector4 color = {0.f, 0.f, 0.f, 1.f}, float d = 0.7f);
	virtual ~Particle();

	void integrateEuler(double t);
	void integrateEulerSemi(double t);
	void integrateVerlet(double t);

protected:
	Vector3D<float> vel, a;
	Vector4 color;
	physx::PxTransform pos, antPos;

	float d = 0.7f, size;
	bool firstMove = true;

	RenderItem* renderItem;
};