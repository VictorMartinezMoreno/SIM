#include "ForceFactory.h"
#include "ParticleFactory.h"
#include "ForceEmitter.h"
#include <utility>

ForceFactory::ForceFactory(const std::vector<ParticleFactory*>& systems)
	: m_emitters(), m_particles() {
	for (auto& e : systems) {
		std::vector<Particle*>& pv = e->getParticles();
		m_particles.insert(m_particles.end(), pv.begin(), pv.end());
	}
}

ForceFactory::ForceFactory(const std::vector<Particle*>& particles)
	: m_emitters(), m_particles() {
	m_particles = particles;
}

ForceFactory::ForceFactory(const std::vector<ParticleFactory*>& systems, const std::vector<Particle*>& particles)
	: m_emitters(), m_particles() {

	m_particles = particles;
	for (auto& e : systems) {
		const std::vector<Particle*>& pv = e->getParticles();
		m_particles.insert(m_particles.end(), pv.begin(), pv.end());
	}
}

ForceFactory::~ForceFactory() {
	for (auto& m_emitter : m_emitters) {
		delete m_emitter;
		m_emitter = nullptr;
	}
	m_emitters.clear();
}

void ForceFactory::addForceEmitter(ForceEmitter* em) {
	m_emitters.push_back(em);
}

void ForceFactory::update(double dt) {
	for (auto& em : m_emitters) {
		for (auto& p : m_particles) {
			if (em->isActive() && em->inArea(p)) {
				em->applyForce(p);
			}
		}
	}
}
