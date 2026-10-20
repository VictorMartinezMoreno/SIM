#pragma once

#include "Proyectile.h"

class Ash : public Proyectile {
protected:
	virtual void update(double dt) override;
public:
	Ash(Vector3D<float> Pos, Vector3D<float> Vel, float masa, float lifeTime = 1000.f, float size = 1.0f, Vector4 color = { 0.0f, 0.0f, 0.0f, 1.0f }, float d = 0.7f);
	virtual ~Ash() = default;
protected:
};