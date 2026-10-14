#include "Scene3.h"
#include "ParticleFactory.h"
#include "EllipsoidEmitter.h"

void Scene3::init() {
	m_factory = new ParticleFactory();

	//ParticleFactory* f0 = ParticleFactory::createCircleGenerator({ 0, 0, 0 }, { 0, 1, 0 }, 50.f, 0.f, 3.f, 1.f, 2000.f, ParticleFactory::TYPE::PROYECTILE, 0.0f, 1.0f, 1.f, true);
	//ParticleFactory* f1 = ParticleFactory::createSquareGenerator({ 100, 0, 0 }, { 0, 1, 0 }, 50.f, 0.f, 3.f, 200.f, 500.f, ParticleFactory::TYPE::PROYECTILE, 0.0f, 1.0f, 1.f, true);
	//ParticleFactory* f2 = ParticleFactory::createRectangleGenerator({ -100, 0, 0 }, { 0 ,1 ,0 }, 50.f, 0.f, 0.f, 3.f, 6.f, 100.f, 1200.f, ParticleFactory::TYPE::PROYECTILE, 0.0f, 1.0f, 1.f, true);
	EllipsoidEmitter* f3 = new EllipsoidEmitter(m_factory, { 50, 0, 0 }, { 0.f, 1.f, 0.f }, 10.f, 50.f, 20.f, 10.f, 20.5f, ParticleType::PROYECTILE, 0.0f, 1.0f, 1.0f, true);

	//m_factories.push_back(f0);
	//m_factories.push_back(f1);
	//m_factories.push_back(f2);
	m_emitters.push_back(f3);
}

void Scene3::update(double dt) {
	if (m_factory) m_factory->update(dt);
	for (auto& emitter : m_emitters) {
		emitter->createParticle(dt);
	}
}

void Scene3::keyPress(unsigned char key, const physx::PxTransform& camera) {

}

void Scene3::cleanup() {
	if (m_factory) {
		delete m_factory;
		m_factory = nullptr;
	}
	for (auto& emitter : m_emitters) {
		delete emitter;
		emitter = nullptr;
	}
	m_emitters.clear();
}
