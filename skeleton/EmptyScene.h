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

        m_Utransform = physx::PxTransform(u);
        m_Vtransform = physx::PxTransform(v);
        m_Wtransform = physx::PxTransform(w);
		m_Jtransform = physx::PxTransform(j);

        // Se registra el RenderItem exactamente como en la plantilla original
        Vector4 color = {1.0f, 0.0f, 0.0f, 1.0f};

        m_renderItems.push_back(new RenderItem(shape, &m_Utransform, color));
        m_renderItems.push_back(new RenderItem(shape, &m_Vtransform, color));
        m_renderItems.push_back(new RenderItem(shape, &m_Wtransform, color));
		m_renderItems.push_back(new RenderItem(shape, &m_Jtransform, color));

        //Recorremos todos los elementos renderizables y cambiamos su color en función del producto escalara con el vector director de la visión del personaje
        //Los vectores que se usan para calcular esto es la propia posición porque suponemos que el origen de todos es 0,0,0 y V=B-A -> V=B-0 -> V=B.
        for (auto& m_renderItem : m_renderItems) {
            float prod = d.dot(m_renderItem->transform->p);
            if (prod < 0) m_renderItem->color = {0.0f, 1.0f, 0.0f, 1.0f}; // Verde si el producto escalar es negativo
            else if (prod > 0) m_renderItem->color = {1.0f, 0.0f, 0.0f, 1.0f}; // Rojo si el producto escalar es positivo
            else m_renderItem->color = { 1.0f, 1.0f, 0.0f, 1.0f }; // Amarillo si el producto escalar es cero
		}
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
            m_Jtransform = physx::PxTransform(j);
        }
    }

    void cleanup() override {
        for (auto& m_renderItem : m_renderItems) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
    }

private:
    Vector3D<float> u = Vector3D<float>(2.0f, 0.0f, 3.0f);
    Vector3D<float> v = Vector3D<float>(-4.0f, 0.0f, 1.0f);
    Vector3D<float> w = Vector3D<float>(0.0f, 0.0f, -5.0f);
    Vector3D<float> j = Vector3D<float>(3.0f, 0.0f, 0.0f);

	Vector3D<float> d = Vector3D<float>(0.0f, 0.0f, 1.0f);


    physx::PxTransform m_Utransform;
    physx::PxTransform m_Vtransform;
    physx::PxTransform m_Wtransform;
    physx::PxTransform m_Jtransform;

    std::vector<RenderItem*> m_renderItems;
};