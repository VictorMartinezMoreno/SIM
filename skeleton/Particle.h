#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle {
protected:
	virtual void update(double dt) {};
public:
	Particle(Vector3D<float> Pos, Vector3D<float> Vel, float lifeTime = 1000.f, Vector3D<float> ac = { 0.0f, -10.f, 0.0f }, float size = 1.f, Vector4 color = { 0.f, 0.f, 0.f, 1.f }, float d = 0.7f);
	virtual ~Particle();

	void integrateEuler(double t);
	void integrateEulerSemi(double t);
	void integrateVerlet(double t);

	inline void decreaseLifeTime(float t) noexcept { currLifeTime -= t; }
	inline float getLifeTime() const noexcept { return currLifeTime; }

	inline void setColor(Vector4 color) noexcept { this->color = color; }
	inline virtual void setLifeTime(float t) noexcept { maxLifeTime = t; currLifeTime = t; }
	inline void setPos(physx::PxTransform pos) noexcept { this->pos = pos; }
	inline void setSize(float size) noexcept {
		maxSize = size;
		this->size = maxSize;
	}
	virtual inline void setVel(Vector3D<float> vel) { this->vel = vel; }
	inline void setActive(bool visible);

protected:
	Vector3D<float> vel, a;
	Vector4 color;
	physx::PxTransform pos, antPos;

	float d = 0.7f, size, maxSize;
	bool firstMove = true;
	float currLifeTime, maxLifeTime; //Miliseconds

	RenderItem* renderItem;
};