#include "Scene4.h"
#include "CircleEmitter.h"
#include "GravityEmitter.h"
#include "WindEmitter.h"
#include "TornadoEmitter.h"
#include "ForceFactory.h"
#include "Ellipsoid.h"
#include "Box.h"
#include "Particle.h"

void Scene4::init() {
	m_pFactory = new ParticleFactory(3000);
	std::vector<ParticleFactory*> v = { m_pFactory };
	m_fFactory = new ForceFactory(v);

	


	CircleEmitter* f0 = new	CircleEmitter(m_pFactory, { 10.f, 0.f, 0.f }, { 0.f, 1.f, 0.f }, 1.f, 0.f, 0.1f, 0.1f, 0.2f, ParticleType::PROYECTILE, 2000000, { 1.f,1.f,0.f,1.f }, 1.f, 0.1f);
	new WindEmitter(m_fFactory, new Box({ 0, -1, 0 }, { 0, 1, 0 }, 100.f, 10.f, 100.f, 10.f, 50.f), 500.f, 0.1f, 50.f);
	new GravityEmitter(m_fFactory, new Ellipsoid({ 0, -1, 0 }, { 0,1,0 }, 100.f, 500.f, 100.f), 10.f);
	new TornadoEmitter(m_fFactory, new Ellipsoid({ 0, -1 , 0 }, { 0, 1, 0 }, 50, 1000, 50), 1000000.f, 0.1f);

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

