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
	wind = new WindEmitter(m_fFactory, new Box({ 0, -1, 0 }, { 0, 1, 0 }, 100.f, 10.f, 100.f, 10.f, 50.f), 500.f, 0.1f, 50.f);
	grav = new GravityEmitter(m_fFactory, new Ellipsoid({ 0, -1, 0 }, { 0,1,0 }, 100.f, 500.f, 100.f), 10.f);
	torn = new TornadoEmitter(m_fFactory, new Box({ 0, -1 , 0 }, { 0, 1, 0 }, 100, 100, 100, 100, 500), 100.f, 0.1f);

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
	if (key == 'r' || key == 'R') {
		cleanup();
		init();
	}
	else if (key == 'z' || key == 'Z') grav->activate(!grav->isActive());
	else if (key == 'x' || key == 'X') wind->activate(!wind->isActive());
	else if (key == 'c' || key == 'C') torn->activate(!torn->isActive());
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

