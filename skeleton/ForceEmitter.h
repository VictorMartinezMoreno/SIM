#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "ForceFactory.h"
#include "geometry.h"
#include "Particle.h"
#include <vector>
#include <functional>
#include <random>

class ForceEmitter {
protected:
	ForceFactory* m_factory;
	Geometry* m_geo;
	float m_force; //La fuerza aplicada se mide en Newtons
	float m_force_reduction; //Altura a la que la fuerza es 0, haciendo un gradiente entre 0 y esa altura. Si es -1, no hay reducción.
	bool m_active;

public:
	//Redefinir para generar la forma del emisor, esférico, cónico, cúbico...
	virtual bool inArea(Particle* p) { return m_geo->inArea(p->getPos()); }
	//Redefinir para decidir como aplicar la fuerza en las particulas
	virtual void applyForce(Particle* p) = 0;

	inline void activate(bool activate) noexcept { m_active = activate; }
	inline bool isActive() const noexcept { return m_active; }

	inline Vector3D<float>& getPos() noexcept { return m_geo->getPosition(); }
	inline Vector3D<float>& getDir() noexcept { return m_geo->getDirection(); }

	virtual ~ForceEmitter() {
		if (m_geo) {
			delete m_geo;
			m_geo = nullptr;
		}
	}

protected:
	//Constructora protegida porque no interesa que nadie cree un objeto ForceEmitter,
	//nos interesa solo que sus hijos lo creen.
	ForceEmitter(
		ForceFactory* factory,
		Geometry* geo,
		float force,
		float forceReduction = -1.f,
		bool active = true)
		: m_factory(factory), m_geo(geo), m_force(force), m_force_reduction(forceReduction), m_active(active) {
		if (factory) factory->addForceEmitter(this);
	}
};