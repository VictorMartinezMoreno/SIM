#pragma once

#include "Emitter.h"

class BoxEmitter : public Emitter {
protected:
	virtual Vector3D<float> newPosition() override;
	virtual Vector3D<float> newDirection(const Vector3D<float>& pos) override;

public:
	BoxEmitter(
		ParticleFactory* factory,
		Vector3D<float> position,
		Vector3D<float> direction,
		float width, float height, float depth,
		float m_minVel, float m_maxVel,
		ParticleType type,
		float mean = 0.f, float stdD = 1.f,
		float freq = 1.f,
		bool active = false
	);

	virtual ~BoxEmitter() = default;

protected:
	float width;
	float height;
	float depth;
};