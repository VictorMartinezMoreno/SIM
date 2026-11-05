#pragma once

#include "ForceEmitter.h"

class GravityEmitter : public ForceEmitter {
public:
	GravityEmitter(
		ForceFactory* factory,
		Geometry* geo,
		float force,
		float forceReduction = -1.f,
		bool active = true)
		: ForceEmitter(factory, geo, force, forceReduction, active) {
	};

	virtual void applyForce(Particle* p) override;
};