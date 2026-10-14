#pragma once

#include "Emitter.h"

class EllipsoidEmitter : public Emitter {
protected:
	virtual Vector3D<float> newPosition() override;
	virtual Vector3D<float> newDirection(const Vector3D<float>& pos) override;

public:
	EllipsoidEmitter(
		ParticleFactory* factory,
		Vector3D<float> position,
		Vector3D<float> direction,
		float widthRadius, float heightRadius, float depthRadius,
		float m_minVel, float m_maxVel,
		ParticleType type,
		float mean = 0.f, float stdD = 1.f,
		float freq = 1.f,
		bool active = false
	);

	virtual ~EllipsoidEmitter() = default;

protected:
	float widthRadius;
	float heightRadius;
	float depthRadius;
};