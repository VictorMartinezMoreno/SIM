
#pragma once

#include "Vector3D.h"
#include <vector>
#include <functional>
#include <unordered_map>
#include <random>

class Particle;
class Emitter;

//Para añadir nuevas particulas hay que:
// - Añadir el enum.
// - Añadir la creación de pool en la constructora.
// - En el update de Emitter.h añadir la recogida de esa particula.

enum ParticleType {
	PROYECTILE,
	ASH,
	SPARK,
	NUM_TYPES
};

class ParticleFactory {
	friend Emitter;
protected:
	Particle* getParticle(ParticleType t);
public:
	ParticleFactory(int maxParticles = 1000);
	~ParticleFactory();

	void update(double dt);
protected:
	std::unordered_map<ParticleType, std::vector<Particle*>> m_particles;
};