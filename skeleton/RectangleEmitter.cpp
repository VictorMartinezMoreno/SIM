#include "RectangleEmitter.h"

RectangleEmitter::RectangleEmitter(ParticleFactory* factory, Vector3D<float> position, Vector3D<float> direction, float depth, float groundWidth, float groundHeight, float airWidth, float airHeight, float m_minVel, float m_maxVel, ParticleType type, float lifeTime, Vector4 color, float pSize, float freq, float mean, float stdD, bool active)
: Emitter(factory, position, direction, m_minVel, m_maxVel, type, color, lifeTime, pSize, freq, mean, stdD, active), depth(depth), groundWidth(groundWidth), groundHeight(groundHeight), airWidth(airWidth), airHeight(airHeight) {
}

Vector3D<float> RectangleEmitter::newPosition() {
	const float
		x = m_position.getX() + groundWidth / 2 * newFloat(-1.f, 1.f),
		y = m_position.getY(),
		z = m_position.getZ() + groundHeight / 2 * newFloat(-1.f, 1.f);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

	return position;
}

Vector3D<float> RectangleEmitter::newDirection(const Vector3D<float>& pos) {
	const float
		x = m_position.getX() + airWidth / 2 * newFloat(-1.f, 1.f),
		y = m_position.getY() + depth,
		z = m_position.getZ() + airHeight / 2 * newFloat(-1.f, 1.f);

	Vector3D<float> position = { x, y, z };
	rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);
	return (position - pos).normalize();
}
