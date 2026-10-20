#include "Particle.h"
#include "Proyectile.h"
#include "ParticleFactory.h"
#include "Ash.h"
#include "Spark.h"

ParticleFactory::ParticleFactory(int maxParticles)
	: m_particles() {

	const int
		particlePerType = maxParticles / NUM_TYPES,
		rest = maxParticles % NUM_TYPES;

	//Creamos particulas de forma equilibrada para cada tipo de particula
	for (int i = 0; i < NUM_TYPES; i++) {
		const ParticleType particle = (ParticleType) i;
		m_particles.insert({ particle, std::vector<Particle*>() });

		for (int j = 0; j < particlePerType; j++) {
			switch (particle) {
			case PROYECTILE:
				m_particles.at(particle).push_back(new Proyectile({0,0,0}, {0,0,0}, 0, 0));
				break;
			case ASH:
				m_particles.at(particle).push_back(new Ash({ 0,0,0 }, { 0,0,0 }, 0, 0));
				break;
			case SPARK:
				m_particles.at(particle).push_back(new Spark({ 0,0,0 }, { 0,0,0 }, 0, 0));
				break;
			default:
				break;
			}
		}
	}

	//Si la división entera no es exacta, lo que sobre lo creamos en proyectiles (que suele ser la partícula mas usada)
	for (int i = 0; i < rest; i++) m_particles.at(PROYECTILE).push_back(new Proyectile({ 0,0,0 }, { 0,0,0 }, 0, 0));
}

ParticleFactory::~ParticleFactory() {
	for (auto& v : m_particles) {
		for (auto& p : v.second) {
			delete p;
			p = nullptr;
		}
		v.second.clear();
	}
	m_particles.clear();
}

//Si no hay ninguna particula desactivada, devuelve nullptr.
Particle* ParticleFactory::getParticle(ParticleType t) {
	int i = 0;
	bool enc = false;
	const std::vector<Particle*>& vec = m_particles.at(t);

	while (i < vec.size() && !enc) {
		enc = vec.at(i)->getLifeTime() <= 0;
		if (!enc) i++;
	}

	if (enc) return vec.at(i);
	else return nullptr;
}

void ParticleFactory::update(double dt) {
	for (auto& v : m_particles) {
		auto& pp = v.second[0];
		for (auto& p : v.second) {
			if (p->getLifeTime() > 0) {
				p->integrateEulerSemi(dt);
				p->decreaseLifeTime(dt*1000);
				
				if (p->getLifeTime() <= 0) {
					p->setActive(false);
				}
			}
		}
	}
}
