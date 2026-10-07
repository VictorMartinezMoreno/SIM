#include "Scene2.h"
#include "Proyectile.h"
#include "RenderUtils.hpp"

#include <iostream>

void Scene2::init() {
	
}

void Scene2::update(double dt) {
	for (auto& m_particle : m_proyectiles) {
		m_particle->integrateVerlet(dt);
	}
}

void Scene2::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'r' || key == 'R') {
		cleanup();
		init();
	}
	else if (key == '+') {
		for (auto& m_particle : m_proyectiles) {
			masaPistola += 0.1f;
			masaTanque += 0.1f;
			masaCanon += 0.1f;
		}
	}
	else if (key == '-') {
		for (auto& m_particle : m_proyectiles) {
			masaPistola -= 0.1f;
			masaTanque -= 0.1f;
			masaCanon -= 0.1f;
		}
	}
	else if (key == 'z') {
		Camera* cam = __RENDER_UTILS_H__::GetCamera();
		Vector3D<float> shootDir = cam->getDir();
		Vector3D<float> camPos = cam->getEye() + shootDir * 1.5f; //Avoid cam collision with the proyectile

		m_proyectiles.push_back(new Proyectile(camPos, shootDir * 330.f, masaPistola));
	}
	else if (key == 'x' || key == 'X') {
		Camera* cam = __RENDER_UTILS_H__::GetCamera();
		Vector3D<float> shootDir = cam->getDir();
		Vector3D<float> camPos = cam->getEye() + shootDir * 1.5f; //Avoid cam collision with the proyectile

		m_proyectiles.push_back(new Proyectile(camPos, shootDir * 1800.f, masaTanque));
	}
	else if (key == 'c' || key == 'C') {
		Camera* cam = __RENDER_UTILS_H__::GetCamera();
		Vector3D<float> shootDir = cam->getDir();
		Vector3D<float> camPos = cam->getEye() + shootDir * 1.5f; //Avoid cam collision with the proyectile

		m_proyectiles.push_back(new Proyectile(camPos, shootDir * 250.f, masaCanon));
	}
}

void Scene2::cleanup() {
	for (auto& m_particle : m_proyectiles) {
		delete m_particle;
		m_particle = nullptr;
	}
	m_proyectiles.clear();
}
