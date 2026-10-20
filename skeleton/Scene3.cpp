#include "BoxEmitter.h"
#include "CircleEmitter.h"
#include "CubeEmitter.h"
#include "EllipsoidEmitter.h"
#include "ParticleFactory.h"
#include "RectangleEmitter.h"
#include "Scene3.h"
#include "SphereEmitter.h"
#include "SquareEmitter.h"

void Scene3::init() {
	m_factory = new ParticleFactory(5000);

	//EMISOR EN AREA CON PARTÍCULAS QUE IMITAN LUCIERNAGAS
	SphereEmitter* f0 = new SphereEmitter(m_factory, { 0, 0, 0 }, 25.f, 20.f, 50.f, ParticleType::SPARK, 10000, { 1.f,1.f,0.f,1.f }, 1.f, 0.1f);
	
	//EMISOR CON PARTÍCULAS QUE IMITAN HUMO DISIPANDOSE
	CircleEmitter* f4 = new CircleEmitter(m_factory, { -200, 0, 0 }, { 0, 1, 0 }, 1.f, 0.0, 0.2, 1000, 1200, ParticleType::ASH, 5000, {0.4, 0.4, 0.4, 1.f}, 7, 0.5);

	m_emitters.push_back(f0);
	m_emitters.push_back(f4);
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
