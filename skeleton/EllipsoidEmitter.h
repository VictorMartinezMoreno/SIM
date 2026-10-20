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
		float lifeTime = 1000.f,
		Vector4 color = {0.f,0.f,0.f,1.f},
		float pSize = 1.f,
		float freq = 1.f,
		float mean = 0.f, float stdD = 1.f,
		bool active = true
	);

	virtual ~EllipsoidEmitter() = default;

protected:
	float widthRadius;
	float heightRadius;
	float depthRadius;
};