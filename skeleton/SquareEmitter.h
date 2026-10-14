#pragma once

#include "Emitter.h"

class SquareEmitter : public Emitter {
protected:
	virtual Vector3D<float> newPosition() override;
	virtual Vector3D<float> newDirection(const Vector3D<float>& pos) override;
public:
	SquareEmitter(
		ParticleFactory* factory,
		Vector3D<float> position,
		Vector3D<float> direction,
		float depth,
		float groundSize,
		float airSize,
		float m_minVel, float m_maxVel,
		ParticleType type,
		float mean = 0.f, float stdD = 1.f,
		float freq = 1.f,
		bool active = false
	);

	virtual ~SquareEmitter() = default;
protected:
	float groundSize;
	float airSize;
	float depth;
};