#pragma once

#include "ForceEmitter.h"

class TornadoEmitter : public ForceEmitter {
public:
	TornadoEmitter(
		ForceFactory* factory,
		Geometry* geo,
		float force,
		float k1,
		float forceReduction = -1.f,
		bool active = true)
		: ForceEmitter(factory, geo, force, forceReduction, active), m_k1(k1) {
	};

	virtual void applyForce(Particle* p) override;
protected:
	float m_k1; //Fuerza de rozamiento
};