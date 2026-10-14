#pragma once

#include "Vector3D.h"
#include <vector>
#include <functional>
#include <random>

class Particle;

class ParticleFactory {
public:
	ParticleFactory() : m_particles() {};
	~ParticleFactory();

	void update(double dt);

	inline void addParticle(Particle* p) { m_particles.push_back(p); }
protected:

	std::vector<Particle*> m_particles;
};