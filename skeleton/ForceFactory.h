
#pragma once

#include <vector>
#include <functional>
#include <random>
#include "Vector3D.h"

class ParticleFactory;
class Particle;
class ForceEmitter;

class ForceFactory {
	friend ForceEmitter;
protected:
	std::vector<ForceEmitter*> m_emitters; //Vector de emisores en el sistema.
	std::vector<Particle*> m_particles; //Vector de particulas dentro de un campo.
public:
	ForceFactory(const std::vector<ParticleFactory*>& systems);
	ForceFactory(const std::vector<Particle*>& particles);
	ForceFactory(const std::vector<ParticleFactory*>& systems, const std::vector<Particle*>& particles);

	~ForceFactory();

	void update(double dt);
protected:
	void addForceEmitter(ForceEmitter* em);
};