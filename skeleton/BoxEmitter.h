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
		float lifeTime = 1000.f,
		Vector4 color = {0.f,0.f,0.f,1.f},
		float pSize = 1.f,
		float freq = 1.f,
		float mean = 0.f, float stdD = 1.f,
		bool active = true
	);

	virtual ~BoxEmitter() = default;

protected:
	float width;
	float height;
	float depth;
};