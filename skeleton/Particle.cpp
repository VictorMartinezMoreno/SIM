#include "Particle.h"

Particle::Particle(Vector3D<float> Pos, Vector3D<float> Vel, Vector3D<float> ac)
	: pos(Pos), vel(Vel) {

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.2f));
	renderItem = new RenderItem(shape, &pos, { 0.0f, 1.0f, 0.0f, 1.0f });
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
}

void Particle::integrateEulerSemi(double t) {
	firstMove = false;

	const physx::PxTransform aux = pos;

	vel += a * t;
	vel *= pow(d,t);
	pos.p += vel * t;

	antPos = aux;
}

void Particle::integrateVerlet(double t) {

	if (firstMove) integrateEuler(t);
	else {
		const physx::PxTransform aux = pos;
		pos.p = (pos.p * 2.0f) - antPos.p + (a * t * t);
		antPos = aux;
	}
}
