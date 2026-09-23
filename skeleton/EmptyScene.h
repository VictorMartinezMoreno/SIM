#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        u = u.normalize();
        v = v.normalize();
        w = w.normalize();

		u *= 5.0f;
		v *= 5.0f;
		w *= 5.0f;

        physx::PxShape* Ushape = CreateShape(physx::PxSphereGeometry(1.0f));
        physx::PxShape* Vshape = CreateShape(physx::PxSphereGeometry(1.0f));
        physx::PxShape* Wshape = CreateShape(physx::PxSphereGeometry(1.0f));

        m_Utransform = physx::PxTransform(u);
        m_Vtransform = physx::PxTransform(v);
        m_Wtransform = physx::PxTransform(w);

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItems.push_back(new RenderItem(Ushape, &m_Utransform, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
        m_renderItems.push_back(new RenderItem(Vshape, &m_Vtransform, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
        m_renderItems.push_back(new RenderItem(Wshape, &m_Wtransform, Vector4(0.0f, 0.0f, 1.0f, 1.0f)));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_Utransform = physx::PxTransform(u);
            m_Vtransform = physx::PxTransform(v);
            m_Wtransform = physx::PxTransform(w);
        }
    }

    void cleanup() override {
        for (auto& m_renderItem : m_renderItems) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
    }

private:
    Vector3D<float> u = Vector3D<float>(3.0f, 1.0f, 0.0f);
    Vector3D<float> v = Vector3D<float>(0.0f, 4.0f, 0.0f);
    //Si se cambia el orden en el que se obtiene el producto vectorial, el vector resultante tendrá la dirección contraria,
	//esto se puede observar con la regla de la mano derecha, que indica la dirección del producto vectorial.
	Vector3D<float> w = u.cross(v);

    physx::PxTransform m_Utransform;
    physx::PxTransform m_Vtransform;
    physx::PxTransform m_Wtransform;

    std::vector<RenderItem*> m_renderItems;
};