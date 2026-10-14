#include "Particle.h"

Particle::Particle(Vector3D<float> Pos, Vector3D<float> Vel, Vector3D<float> ac, float size, Vector4 color, float d)
	: pos(Pos), vel(Vel), color(color), d(d), size(size) {

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(size));
	renderItem = new RenderItem(shape, &pos, color);
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
