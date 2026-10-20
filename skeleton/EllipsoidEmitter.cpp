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
		r1 = newFloat(0.f, 1.f),
		a1 = newFloat(0.f, 2.f * M_PI);

	const float
		xRel = widthRadius * r1 * cosf(a1),
		yRel = heightRadius * r1 * sinf(a1);

	//Tenemos un punto aleatorio en el plano dos dimensiones de una elipse
	// Si usamos la formula r * cos(a) con los radios mayor y menor de una elipse, puedes encontrar un punto aleatorio en él.
	const float
		x = m_position.getX() + xRel,
		y = m_position.getY() + yRel;

	const float
		componentXY = (xRel * xRel) / (widthRadius * widthRadius) + (yRel * yRel) / (heightRadius * heightRadius),
		zMax = depthRadius * std::sqrtf(max(0.f, 1.f - componentXY)),
		z = m_position.getZ() + (zMax * newFloat(-1.f, 1.f));

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

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
