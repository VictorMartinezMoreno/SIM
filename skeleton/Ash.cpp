#include "Ash.h"

void Ash::update(double dt) {
	if (maxSize != 0 && ((size - (maxSize / (maxLifeTime / (dt * 1000)))) > 0)) {
		size -= maxSize / (maxLifeTime / (dt * 1000));
		
		if (renderItem) {
			renderItem->release();

			physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(size));
			renderItem = new RenderItem(shape, &pos, color);
		}
	}
}

Ash::Ash(Vector3D<float> Pos, Vector3D<float> Vel, float masa, float lifeTime, float size, Vector4 color, float d)
: Proyectile(Pos, Vel, masa, lifeTime, size, color, d) {
}
