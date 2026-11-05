#define _USE_MATH_DEFINES
#include <cmath>
#include "Ellipsoid.h"

Ellipsoid::Ellipsoid(Vector3D<float> pos, Vector3D<float> dir, float w, float h, float d) noexcept
	: Geometry(pos, dir), m_widthRadius(w), m_heightRadius(h), m_depthRadius(d) {
}

bool Ellipsoid::inArea(const Vector3D<float>& pos) const {
	//Obtenemos el punto basandonos en que la geometria apunta en dirección UP.
	Vector3D<float> position = pos;
	Geometry::rotatePoint(position, m_direction, { 0, 1, 0 }, m_position);

	//Una vez hemos rotado el espacio simulado que contiene el punto y la geometría, podemos comprobar fácilmente basandonos en que ambos
	//están apuntando hacia arriba, es decir, la dirección de la geometría es UP y el el punto en el espacio ahora está posicionado respecto a eso.
	const double coef =
		std::pow(position.getX() - m_position.getX(), 2) / std::pow(m_widthRadius, 2) +
		std::pow(position.getY() - m_position.getY(), 2) / std::pow(m_heightRadius, 2) +
		std::pow(position.getZ() - m_position.getZ(), 2) / std::pow(m_depthRadius, 2);

	return coef <= 1.0f;
}

Vector3D<float> Ellipsoid::rdmPoint(std::function<float(float, float)> newFloat, float depth) const {
	const float h = m_heightRadius - depth;

	const float
		r1 = m_widthRadius * newFloat(0.f, 1.f),
		r2 = depth == -1? m_heightRadius * newFloat(0.f, 1.f) : h,
		r3 = m_depthRadius * newFloat(0.f, 1.f),
		a1 = newFloat(0.f, 2.f * M_PI),
		a2 = newFloat(0.f, M_PI);

	//Fórmula de coordenada elipsoidal:
	// x = r1 sen(a) cos(b)
	// y = r2 sen(a) sen(b)
	// z = r3 cos(a)
	const float
		x = m_position.getX() + r1 * std::sinf(a2) * std::cosf(a1),
		y = m_position.getY() + r2 * std::sinf(a2) * std::sinf(a1),
		z = m_position.getZ() + r3 * std::cosf(a2);

	Vector3D<float> position = { x, y, z };

	Geometry::rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

	return position;
}
