#pragma once

#include "Emitter.h"

class RectangleEmitter : public Emitter {
protected:
	virtual Vector3D<float> newPosition() override;
	virtual Vector3D<float> newDirection(const Vector3D<float>& pos) override;
public:
	RectangleEmitter(
		ParticleFactory* factory,
		Vector3D<float> position,
		Vector3D<float> direction,
		float depth,
		float groundWidth, float groundHeight,
		float airWidth, float airHeight,
		float m_minVel, float m_maxVel,
		ParticleType type,
		float mean = 0.f, float stdD = 1.f,
		float freq = 1.f,
		bool active = false
	);

	virtual ~RectangleEmitter() = default;

protected:
	float groundWidth, groundHeight;
	float airWidth, airHeight;
	float depth;
};