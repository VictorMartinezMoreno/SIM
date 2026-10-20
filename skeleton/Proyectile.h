#pragma once

#include "Particle.h"

class Proyectile : public Particle {
protected:
	const float velSFactor = 25.0f;

	Vector3D<float> velR;

	float masaR;
	float masaS;
public:
	Proyectile(Vector3D<float> Pos, Vector3D<float> Vel, float masa, float lifeTime = 1000.f, float size = 1.0f, Vector4 color = {0.0f, 0.0f, 0.0f, 1.0f}, float d = 0.7f);
	virtual ~Proyectile() = default;

	void setMass(float mass);
	float getMass() const noexcept { return masaR; }
	virtual void setVel(Vector3D<float> vel) override;
	void setAcceleration(Vector3D<float> acceleration);
protected:

	void changeMassToSimulate();
	void changeAccelerationToSimulate();
};