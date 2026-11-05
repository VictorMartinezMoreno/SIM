#pragma once

#include "Scene.h"
#include "Vector3D.h"
#include <vector>

class ParticleFactory;
class ForceFactory;
class Emitter;

class Scene4 : public Scene {
public:
	explicit Scene4(std::string name) : Scene(std::move(name)) {}

	void init() override;
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;
	void cleanup() override;

private:
	std::vector<Emitter*> m_emitters;
	ParticleFactory* m_pFactory;
	ForceFactory* m_fFactory;
};