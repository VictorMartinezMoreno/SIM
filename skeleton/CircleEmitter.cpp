#define _USE_MATH_DEFINES

#include "CircleEmitter.h"
#include <cmath>

CircleEmitter::CircleEmitter(ParticleFactory* factory, Vector3D<float> position, Vector3D<float> direction, float depth, float groundRadius, float airRadius, float m_minVel, float m_maxVel, ParticleType type, float lifeTime, Vector4 color, float pSize, float freq, float mean, float stdD, bool active)
	: Emitter(factory, position, direction, m_minVel, m_maxVel, type, color, lifeTime, pSize, freq, mean, stdD, active), depth(depth), groundRadius(groundRadius), airRadius(airRadius) {
}

//Para hallar puntos aleatorios en un circulo,
//podemos hallar un angulo aleatorio y dentro de él un punto aleatorio respetando el radio.

Vector3D<float> CircleEmitter::newPosition() {
	const float r = groundRadius * newFloat(0.f, 1.f);
	const float a = newFloat(0.f, 2.f * M_PI);

	const float x = m_position.getX() + r * std::cosf(a);
	const float y = m_position.getY();
	const float z = m_position.getZ() + r * std::sinf(a);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

	return position;
}

Vector3D<float> CircleEmitter::newDirection(const Vector3D<float>& pos) {
	const float r = airRadius * newFloat(0.f, 1.f);
	const float a = newFloat(0.f, 2.f * M_PI);

	const float x = m_position.getX() + r * std::cosf(a);
	const float y = m_position.getY() + depth;
	const float z = m_position.getZ() + r * std::sinf(a);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);
	return (position - pos).normalize();
}
