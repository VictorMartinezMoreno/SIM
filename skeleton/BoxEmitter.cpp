#include "BoxEmitter.h"

BoxEmitter::BoxEmitter(ParticleFactory* factory, Vector3D<float> position, Vector3D<float> direction, float width, float height, float depth, float m_minVel, float m_maxVel, ParticleType type, float lifeTime, Vector4 color, float pSize, float freq, float mean, float stdD, bool active)
	: Emitter(factory, position, direction, m_minVel, m_maxVel, type, color, lifeTime, pSize, freq, mean, stdD, active), width(width), height(height), depth(depth) {
}

//Para hallar puntos aleatorios en un circulo,
//podemos hallar un angulo aleatorio y dentro de él un punto aleatorio respetando el radio.

Vector3D<float> BoxEmitter::newPosition() {

	const float
		x = m_position.getX() + width / 2 * newFloat(-1.f, 1.f),
		y = m_position.getY() + height / 2 * newFloat(-1.f, 1.f),
		z = m_position.getZ() + depth / 2 * newFloat(-1.f, 1.f);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

	return position;
}

Vector3D<float> BoxEmitter::newDirection(const Vector3D<float>& pos) {
	//Como estamos dentro de un area, la particula podrá moverse en cualquier dirección.
	const float x = newFloat(-1.f, 1.f);
	const float y = newFloat(-1.f, 1.f);
	const float z = newFloat(-1.f, 1.f);

	const Vector3D<float> position = { x, y, z };
	return position.normalize();
}