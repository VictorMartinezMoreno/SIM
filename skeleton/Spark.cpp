#include "Spark.h"

void Spark::update(double dt) {

	if (currLifeTime > maxLifeTime / 2) {
		size = acum + maxSize / (maxLifeTime / 2 / (dt * 1000));
	}
	else {
		double sizee = acum - maxSize / (maxLifeTime / 2 / (dt * 1000));
		if (maxLifeTime != 0 && sizee > 0)
			size = acum - maxSize / (maxLifeTime / 2 / (dt * 1000));
	}
	acum = size;

	if (renderItem) {
		renderItem->release();

		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(size));
		renderItem = new RenderItem(shape, &pos, color);
	}
}

Spark::Spark(Vector3D<float> Pos, Vector3D<float> Vel, float masa, float lifeTime, float size, Vector4 color, float d)
	: Proyectile(Pos, Vel, masa, lifeTime, size, color, d), acum(0) {
}
