#define _USE_MATH_DEFINES

#include "EllipsoidEmitter.h"
#include <cmath>

EllipsoidEmitter::EllipsoidEmitter(ParticleFactory* factory, Vector3D<float> position, Vector3D<float> direction, float widthRadius, float heightRadius, float depthRadius, float m_minVel, float m_maxVel, ParticleType type, float lifeTime, Vector4 color, float pSize, float freq, float mean, float stdD, bool active)
	: Emitter(factory, position,direction, m_minVel, m_maxVel, type, color, lifeTime, pSize, freq, mean, stdD, active), widthRadius(widthRadius), heightRadius(heightRadius), depthRadius(depthRadius) {
}

//Para hallar puntos aleatorios en un circulo,
//podemos hallar un angulo aleatorio y dentro de él un punto aleatorio respetando el radio.

Vector3D<float> EllipsoidEmitter::newPosition() {
	const float
		r1 = widthRadius * newFloat(0.f, 1.f),
		r2 = heightRadius * newFloat(0.f, 1.f),
		r3 = widthRadius * newFloat(0.f, 1.f),
		a1 = newFloat(0.f, 2.f * M_PI),
		a2 = newFloat(0.f, M_PI);

	//Fórmula de coordenada elipsoidal:
	// x = r1 sen(a) cos(b)
	// y = r2 sen(a) sen(b)
	// z = r3 cos(a)
	const float
		x = m_position.getX() + r1 * std::sinf(a2) * std::cosf(a1),
		y = m_position.getY() + r2 * std::sinf(a2) * std::sinf(a1),
		z = m_position.getZ() + r3 * std::cosf(a2);

	Vector3D<float> position = { x, y, z };

	return position;
}

Vector3D<float> EllipsoidEmitter::newDirection(const Vector3D<float>& pos) {
	//Como estamos dentro de un area, la particula podrá moverse en cualquier dirección.
	const float x = newFloat(-1.f, 1.f);
	const float y = newFloat(-1.f, 1.f);
	const float z = newFloat(-1.f, 1.f);

	const Vector3D<float> position = { x, y, z };
	return position.normalize();
}
