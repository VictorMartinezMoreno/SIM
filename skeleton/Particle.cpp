#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3D<float> Pos, Vector3D<float> Vel, float lifeTime, float m, Vector3D<float> ac, float size, Vector4 color, float d)
	: pos(Pos), vel(Vel), a(ac), ac({ 0,0,0 }), color(color), d(d), size(size), maxSize(size), masaS(m), currLifeTime(lifeTime), maxLifeTime(lifeTime), renderItem(nullptr) {
	setActive(lifeTime > 0);
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::addForce(const Vector3D<float>& force) {
	ac += force / masaS;
}

void Particle::integrateEuler(double t) {
	firstMove = false;

	const physx::PxTransform aux = pos;

	pos.p += vel * t;
	vel += (a + ac) * t;

	antPos = aux;

	update(t);

	ac = { 0,0,0 };
}

void Particle::integrateEulerSemi(double t) {
	firstMove = false;

	const physx::PxTransform aux = pos;

	vel += (a + ac) * t;
	vel *= pow(d,t);
	pos.p += vel * t;

	antPos = aux;

	update(t);

	ac = { 0,0,0 };
}

void Particle::integrateVerlet(double t) {

	if (firstMove) integrateEuler(t);
	else {
		const physx::PxTransform aux = pos;
		pos.p = (pos.p * 2.0f) - antPos.p + ((a + ac) * t * t);
		antPos = aux;
	}

	update(t);

	ac = { 0,0,0 };
}

inline void Particle::setActive(bool visible) {
	if (visible && !renderItem) {
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(size));
		renderItem = new RenderItem(shape, &pos, color);

		firstMove = true;
	}
	else if (!visible && renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}
