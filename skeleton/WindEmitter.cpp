#include "WindEmitter.h"

void WindEmitter::applyForce(Particle* p) {
    Vector3D<float> distanceVector = (p->getPos() - m_geo->getPosition()) * m_geo->getDirection().normalize();
    float distance = distanceVector.magnitude();

    Vector3D<float> windVelocity;

    if (m_force_reduction < 0) windVelocity = m_geo->getDirection().normalize() * m_force;
    else {
        if (distance >= m_force_reduction) return;
        else {
            float attenuatedSpeed = m_force * (1.0f - (distance / m_force_reduction));
            windVelocity = m_geo->getDirection().normalize() * attenuatedSpeed;
        }
    }

    Vector3D<float> relativeVelocity = windVelocity - p->getVel();;
    Vector3D<float> forceF = relativeVelocity * m_k1;

    p->addForce(forceF);
}
