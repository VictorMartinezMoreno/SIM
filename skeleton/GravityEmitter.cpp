#include "GravityEmitter.h"
#include <iostream>
void GravityEmitter::applyForce(Particle* p) {
	Vector3D<float> directionVector = p->getPos() - m_geo->getPosition();
	float distance = directionVector.magnitude();
	if (distance == 0) return;

    Vector3D<float> forceVector = directionVector.normalize();
    float forceF = 0.0f;

    if (m_force_reduction < 0) forceF = m_force;
    else {
        if (distance >= m_force_reduction) forceF = 0.0f;
        else forceF = m_force * (1.0f - (distance / m_force_reduction));
    }

    auto v = forceVector * (-forceF);

    p->addForce(v);
}