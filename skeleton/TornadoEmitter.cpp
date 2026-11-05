#include "TornadoEmitter.h"

void TornadoEmitter::applyForce(Particle* p) {
	Vector3D<float> pPos = p->getPos();
	Vector3D<float> center = m_geo->getPosition();

	Vector3D<float> relativePos = pPos - center;
	float distance = std::sqrt(relativePos.getX() * relativePos.getX() + relativePos.getZ() * relativePos.getZ());


	Vector3D<float> windVelocity = {
		-m_force * relativePos.getZ(),
		0.0f,
		m_force * relativePos.getX()
	};

	if (m_force_reduction > 0) {
		if (distance >= m_force_reduction) return;
		else windVelocity *= 1.0f - (distance / m_force_reduction);
	}

	Vector3D<float> relativeVelocity = windVelocity - p->getVel();
	Vector3D<float> forceF = relativeVelocity * m_k1;

	p->addForce(forceF);
}
