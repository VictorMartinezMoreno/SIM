#pragma once

#include "Particle.h"

class Proyectile : public Particle {
protected:
	const float velSFactor = 15.0f;

	Vector3D<float> velR;

	float masaR;
	float masaS;

public:
	Proyectile(Vector3D<float> Pos, Vector3D<float> Vel, float masa);
	virtual ~Proyectile() = default;

	void setMass(float mass);
	float getMass() const { return masaR; }

	void setAcceleration(Vector3D<float> acceleration);
protected:

	void changeMassToSimulate();
	void changeAccelerationToSimulate();
};