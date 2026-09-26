#pragma once

#include "Scene.h"
#include "Particle.h"
#include "Vector3D.h"
#include <vector>

class Scene1 : public Scene {
public:
	explicit Scene1(std::string name) : Scene(std::move(name)) {}

	void init() override;
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;
	void cleanup() override;

private:
	std::vector<Particle*> m_particles;
};