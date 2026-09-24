#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>

class EmptyScene : public Scene {
public:
	explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

	void init() override {
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

		m_Atransform = physx::PxTransform(A);
		m_Btransform = physx::PxTransform(B);

		// Se registra el RenderItem exactamente como en la plantilla original
		m_renderItems.push_back(new RenderItem(shape, &m_Atransform, { 1.0f, 0.0f, 0.0f, 1.0f }));
		m_renderItems.push_back(new RenderItem(shape, &m_Btransform, { 1.0f, 0.0f, 0.0f, 1.0f }));

		createVector(10, A, (B - A));
	}

	void update(double dt) override {
		// Lógica/Integración del alumno (por ejemplo, movimiento simple)
		//m_transform.p.y -= static_cast<float>(9.8 * dt);
	}

	void keyPress(unsigned char key, const physx::PxTransform& camera) override {
		if (key == 'r' || key == 'R') {
			m_Atransform = physx::PxTransform(A);
			m_Btransform = physx::PxTransform(B);
			createVector(10, A, (B - A));
		}
	}


	void createVector(unsigned int spheres, Vector3D<float> A, Vector3D<float> dir) {
		clearAuxItems();

		float gap = dir.magnitude() / (spheres + 1);
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));

		for (int i = 1; i <= spheres; i++) {
			m_auxTItems.push_back(new physx::PxTransform(A + (dir.normalize() * gap * i)));
			m_auxRenderItems.push_back(new RenderItem(shape, m_auxTItems[m_auxTItems.size()-1], {1.0f, 1.0f, 0.0f, 1.0f}));
		}
	}

	void clearAuxItems() {
		for (auto& m_auxTItems : m_auxTItems) {
			delete m_auxTItems;
			m_auxTItems = nullptr;
		}
		m_auxTItems.clear();
		for (auto& m_auxRenderItem : m_auxRenderItems) {
			m_auxRenderItem->release();
			m_auxRenderItem = nullptr;
		}
		m_auxRenderItems.clear();
	}

	void cleanup() override {
		for (auto& m_renderItem : m_renderItems) {
			m_renderItem->release(); // Deregistra y destruye el item
			m_renderItem = nullptr;
		}
		m_renderItems.clear();
		clearAuxItems();
	}

private:
	Vector3D<float> A = Vector3D<float>(-8.0f, 1.0f, -8.0f);
	Vector3D<float> B = Vector3D<float>(8.0f, 8.0f, 8.0f);


	physx::PxTransform m_Atransform;
	physx::PxTransform m_Btransform;


	std::vector<RenderItem*> m_auxRenderItems;
	std::vector<physx::PxTransform*> m_auxTItems;
	std::vector<RenderItem*> m_renderItems;
};