#include "Box.h"

Box::Box(Vector3D<float> pos, Vector3D<float> dir, float wA, float hA, float wG, float hG, float d) noexcept
	: Geometry(pos, dir), m_widthAir(wA), m_heightAir(hA), m_widthGround(wG), m_heightGround(hG), m_depth(d) {
}

bool Box::inArea(const Vector3D<float>& pos) const {
	Vector3D<float> position = pos;
	Geometry::rotatePoint(position, m_direction, { 0, 1, 0 }, m_position);

	//Recordamos que damos por hecho que originalmente la fuerza apunta hacia arriba, por lo que la profundidad del campo se da en el ejeY.
	//Si el punto está fuera, obviamente no se encuentra dentro.
	if (position.getY() < m_position.getY() - m_depth / 2 || position.getZ() > m_position.getY() + m_depth / 2) {
		return false;
	}

	//Si está dentro de este campo, hay que ver en función de su Y si se encuentra en un X,Z que cubra el area de la figura.
	//Hayamos entre 0 y 1, qué tan profundo está nuestro punto.
	const double t = (position.getY() - m_position.getY() - (m_depth / 2)) / m_depth;

	//Obtenemos en ese t cuál es el ancho y alto del plano.
	//Además con esto podemos saber cual es el limite en anchura y altura.
	const double
		ancho_actual = m_widthGround + t * (m_widthAir - m_widthGround),
		alto_actual = m_heightGround + t * (m_heightAir - m_widthGround),
		limite_x = ancho_actual / 2.0,
		limite_z = alto_actual / 2.0;

	const bool
		en_x = (position.getX() >= m_position.getX() - limite_x && position.getX() <= m_position.getX() + limite_x),
		en_z = (position.getZ() >= m_position.getZ() - limite_z && position.getZ() <= m_position.getZ() + limite_z);

	return en_x && en_z;
}

Vector3D<float> Box::rdmPoint(std::function<float(float, float)> function, float depth) const {

	const float t = depth == -1 ? function(0.f, 1.f) : depth / m_depth;

	const double
		ancho_actual = m_widthGround + t * (m_widthAir - m_widthGround),
		alto_actual = m_heightGround + t * (m_heightAir - m_widthGround);

	const float
		x = m_position.getX() + (ancho_actual / 2 * function(-1.f, 1.f)),
		y = (m_position.getY() - m_depth / 2) + (m_depth * t),
		z = m_position.getZ() + (alto_actual / 2 * function(-1.f, 1.f));

	Vector3D<float> position = { x ,y ,z };
	Geometry::rotatePoint(position, { 0, 1, 0 }, m_direction, m_position);

	return position;
}
