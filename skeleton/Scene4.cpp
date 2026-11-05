#include "Scene4.h"
#include "CircleEmitter.h"
#include "GravityEmitter.h"
#include "ForceFactory.h"
#include "Ellipsoid.h"
#include "Particle.h"

void Scene4::init() {
	m_pFactory = new ParticleFactory(3000);
	std::vector<ParticleFactory*> v = { m_pFactory };
	m_fFactory = new ForceFactory(v);

	CircleEmitter* f0 = new	CircleEmitter(m_pFactory, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 1.f }, 1.f, 0.f, 0.1f, 1900.f, 2000.f, ParticleType::PROYECTILE, 2000000, { 1.f,1.f,0.f,1.f }, 1.f, 0.1f);
	new GravityEmitter(m_fFactory, new Ellipsoid({ 250,0,0 }, { 0,1,0 }, 500.f, 500.f, 500.f), 50000.f, -1.f);

	m_emitters.push_back(f0);
}

void Scene4::update(double dt) {
	for (auto& emitter : m_emitters) {
		emitter->createParticle(dt);
	}

	if (m_fFactory) m_fFactory->update(dt);
	if (m_pFactory) m_pFactory->update(dt);
}

void Scene4::keyPress(unsigned char key, const physx::PxTransform& camera) {

}

void Scene4::cleanup() {
	if (m_pFactory) {
		delete m_pFactory;
		m_pFactory = nullptr;
	}
	if (m_fFactory) {
		delete m_fFactory;
		m_fFactory = nullptr;
	}
	for (auto& emitter : m_emitters) {
		delete emitter;
		emitter = nullptr;
	}
	m_emitters.clear();
}

