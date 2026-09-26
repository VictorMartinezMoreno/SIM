#include "Scene1.h"

void Scene1::init() {
	m_particles.push_back(new Particle({-8.0f, 1.0f, -8.0f}, { 0.0f, 0.0f, 1.0f }));
}

void Scene1::update(double dt) {
	for (auto& m_particle : m_particles) {
		m_particle->integrateVerlet(dt);
	}
}

void Scene1::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'r' || key == 'R') {
	}
}

void Scene1::cleanup() {
	for (auto& m_particle : m_particles) {
		delete m_particle;
		m_particle = nullptr;
	}
	m_particles.clear();
}
