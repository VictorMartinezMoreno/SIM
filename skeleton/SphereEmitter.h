#pragma once

#include "Emitter.h"

class SphereEmitter : public Emitter {
protected:
	virtual Vector3D<float> newPosition() override;
	virtual Vector3D<float> newDirection(const Vector3D<float>& pos) override;

public:
	SphereEmitter(
		ParticleFactory* factory,
		Vector3D<float> position,
		float radius,
		float m_minVel, float m_maxVel,
		ParticleType type,
		float mean = 0.f, float stdD = 1.f,
		float freq = 1.f,
		bool active = false
	);

	virtual ~SphereEmitter() = default;

protected:
	float radius;
};