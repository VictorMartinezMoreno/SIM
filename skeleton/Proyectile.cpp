#include "Proyectile.h"

Proyectile::Proyectile(Vector3D<float> Pos, Vector3D<float> VelR, float masaR) : Particle(Pos, VelR), masaR(masaR), velR(VelR) {
	//Para calcular la aceleración tenemos en cuenta que F=ma, de forma que a = F/m, siendo F la fuerza de gravedad.
	a = Vector3D<float>(0, -9.8f, 0) * Vector3D<float>(masaR, masaR, masaR);
	vel = VelR / velSFactor;

	changeMassToSimulate();
	changeAccelerationToSimulate();
}

void Proyectile::setMass(float mass) {
	masaR = mass;
	changeMassToSimulate();
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
	float velRM = velR.magnitude();
	float velSM = vel.magnitude();

	float aS = a.magnitude() * (velSM / velRM) * (velSM / velRM);
}
