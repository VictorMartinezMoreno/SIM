#include "Proyectile.h"
#include <iostream>

Proyectile::Proyectile(Vector3D<float> Pos, Vector3D<float> VelR, float masaR, float lifeTime, float size, Vector4 color, float d)
	: Particle(Pos, VelR, lifeTime, {0.f,-10.f,0.f}, size, color, d), masaR(masaR), velR(VelR) {
	vel = velR / velSFactor;

	changeMassToSimulate();
	changeAccelerationToSimulate();
}

void Proyectile::setMass(float mass) {
	masaR = mass;
	changeMassToSimulate();
}

void Proyectile::setVel(Vector3D<float> ve) {

	Vector3D<float> ac = a / (vel / velR) * (vel / velR);

	velR = ve;
	this->vel = velR / velSFactor;

	changeMassToSimulate();
	setAcceleration(ac);
}

void Proyectile::setAcceleration(Vector3D<float> acceleration) {
	a = acceleration;
	changeAccelerationToSimulate();
}

void Proyectile::changeMassToSimulate() {
	float velRM = velR.magnitude();
	float velSM = vel.magnitude();

	masaS = masaR * (velRM/velSM) * (velRM/velSM);
}

void Proyectile::changeAccelerationToSimulate() {
	a = a * (vel / velR) * (vel / velR);
}
