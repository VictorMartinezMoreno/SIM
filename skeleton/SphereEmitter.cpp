
#define _USE_MATH_DEFINES

#include "SphereEmitter.h"
#include "ParticleFactory.h"
#include <cmath>

SphereEmitter::SphereEmitter(ParticleFactory* factory, Vector3D<float> position, float radius, float m_minVel, float m_maxVel, ParticleType type, float lifeTime, Vector4 color, float pSize, float freq, float mean, float stdD, bool active)
	: Emitter(factory, position, { 0, 1, 0 }, m_minVel, m_maxVel, type, color, lifeTime, pSize, freq, mean, stdD, active), radius(radius) {
}

//Para hallar puntos aleatorios en un circulo,
//podemos hallar un angulo aleatorio y dentro de él un punto aleatorio respetando el radio.
Vector3D<float> SphereEmitter::newPosition() {
	const float
		r1 = radius * newFloat(0.f, 1.f),
		a1 = newFloat(0.f, 2.f * M_PI),
		a2 = newFloat(0.f, M_PI);
	
	//Fórmula de coordenada esférica:
	// x = r sen(a) cos(b)
	// y = r sen(a) sen(b)
	// z = r cos(a)
	const float
		x = m_position.getX() + r1 * std::sinf(a2) * std::cosf(a1),
		y = m_position.getY() + r1 * std::sinf(a2) * std::sinf(a1),
		z = m_position.getZ() + r1 * std::cosf(a2);

	Vector3D<float> position = { x, y, z };

	return position;
}

Vector3D<float> SphereEmitter::newDirection(const Vector3D<float>& pos) {
	//Como estamos dentro de un area, la particula podrá moverse en cualquier dirección.
	const float x = newFloat(-1.f, 1.f);
	const float y = newFloat(-1.f, 1.f);
	const float z = newFloat(-1.f, 1.f);

	const Vector3D<float> position = { x, y, z };
	return position.normalize();
}
