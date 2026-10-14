#include "Particle.h"
#include "ParticleFactory.h"

void ParticleFactory::update(double dt) {
	for (auto& p : m_particles) {
		p->integrateEulerSemi(dt);
	}
}

ParticleFactory::~ParticleFactory() {
	for (auto& p : m_particles) {
		delete p;
		p = nullptr;
	}
	m_particles.clear();
}
