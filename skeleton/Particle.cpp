#include "Particle.h"

Particle::Particle(Vector3D<float> Pos, Vector3D<float> Vel)
	: pos(Pos), vel(Vel) {

	const float dt_ = 1.0f / 60.0f;
	antPos = pos;
	antPos.p -= vel * dt_;

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &pos, { 0.0f, 1.0f, 0.0f, 1.0f });
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrateEuler(double t) {
	const physx::PxTransform aux = pos;

	pos.p += vel * t;
	vel += a * t;

	antPos = aux;
}

void Particle::integrateEulerSemi(double t) {
	const physx::PxTransform aux = pos;

	vel += a * t;
	vel *= pow(d,t);
	pos.p += vel * t;

	antPos = aux;
}

void Particle::integrateVerlet(double t) {
	const physx::PxTransform aux = pos;

	pos.p = (pos.p * 2.0f) - antPos.p + (a * t * t);

	antPos = aux;
}
