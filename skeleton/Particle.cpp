#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3D<float> Pos, Vector3D<float> Vel, float lifeTime, Vector3D<float> ac, float size, Vector4 color, float d)
	: pos(Pos), vel(Vel), a(ac), color(color), d(d), size(size), maxSize(size), currLifeTime(lifeTime), maxLifeTime(lifeTime), renderItem(nullptr) {
	setActive(lifeTime > 0);
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrateEuler(double t) {
	firstMove = false;

	const physx::PxTransform aux = pos;

	pos.p += vel * t;
	vel += a * t;

	antPos = aux;

	update(t);
}

void Particle::integrateEulerSemi(double t) {
	firstMove = false;

	const physx::PxTransform aux = pos;

	vel += a * t;
	vel *= pow(d,t);
	pos.p += vel * t;

	antPos = aux;

	update(t);
}

void Particle::integrateVerlet(double t) {

	if (firstMove) integrateEuler(t);
	else {
		const physx::PxTransform aux = pos;
		pos.p = (pos.p * 2.0f) - antPos.p + (a * t * t);
		antPos = aux;
	}

	update(t);
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
