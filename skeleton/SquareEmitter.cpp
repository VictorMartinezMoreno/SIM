#include "SquareEmitter.h"

SquareEmitter::SquareEmitter(ParticleFactory* factory, Vector3D<float> position, Vector3D<float> direction, float depth, float groundSize, float airSize, float m_minVel, float m_maxVel, ParticleType type, float mean, float stdD, float freq, bool active)
	: Emitter(factory, position, direction, m_minVel, m_maxVel, type, mean, stdD, freq, active), depth(depth), groundSize(groundSize), airSize(airSize) {
}

Vector3D<float> SquareEmitter::newPosition() {
	const float
		x = m_position.getX() + groundSize / 2 * newFloat(-1.f, 1.f),
		y = m_position.getY(),
		z = m_position.getZ() + groundSize / 2 * newFloat(-1.f, 1.f);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

	return position;
}

Vector3D<float> SquareEmitter::newDirection(const Vector3D<float>& pos) {
	const float
		x = m_position.getX() + airSize / 2 * newFloat(-1.f, 1.f),
		y = m_position.getY() + depth,
		z = m_position.getZ() + airSize / 2 * newFloat(-1.f, 1.f);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);
	return (position - pos).normalize();
}
