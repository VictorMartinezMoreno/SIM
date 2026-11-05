#include "geometry.h"

Geometry::Geometry(Vector3D<float> pos, Vector3D<float> dir) noexcept
	: m_position(pos), m_direction(dir) {
}

/// <summary>
/// Rota un punto sobre un centro "center"
/// u es la dirección original del punto
/// v es la dirección destino del punto
/// </summary>
/// <param name="position"></param>
/// <param name="u"></param>
/// <param name="v"></param>
/// <param name="center"></param>
void Geometry::rotatePoint(Vector3D<float>& position, const Vector3D<float>& u, const Vector3D<float>& v, const Vector3D<float>& center) {

	// La metodología para calcular los ángulos es:
	// - Proyectamos ambos vectores sobre el plano perpendicular al eje de rotación.
	// - Obtenemos la magnitud de dichas proyecciones en el plano.
	// - Dividimos el producto escalar de los vectores proyectados entre el producto de sus magnitudes.
	// - Obtenemos el ángulo en radianes mediante el arcocoseno (acos), comprobando que la división no sea entre 0.
	// - Determinamos el signo del ángulo mediante el producto cruzado, ya que el arcocoseno siempre devuelve valores positivos.

	const Vector3D<float> uX = { 0.f, u.getY(), u.getZ() };
	const Vector3D<float> vX = { 0.f, v.getY(), v.getZ() };
	const float magX = uX.magnitude() * vX.magnitude();
	float angX = magX > 0.f ? std::acosf(uX.dot(vX) / magX) : 0.f;
	if ((uX.getY() * vX.getZ() - uX.getZ() * vX.getY()) < 0.f) angX = -angX;

	const Vector3D<float> uY = { u.getX(), 0.f, u.getZ() };
	const Vector3D<float> vY = { v.getX(), 0.f, v.getZ() };
	const float magY = uY.magnitude() * vY.magnitude();
	float angY = magY > 0.f ? std::acosf(uY.dot(vY) / magY) : 0.f;
	if ((uY.getZ() * vY.getX() - uY.getX() * vY.getZ()) < 0.f) angY = -angY;

	const Vector3D<float> uZ = { u.getX(), u.getY(), 0.f };
	const Vector3D<float> vZ = { v.getX(), v.getY(), 0.f };
	const float magZ = uZ.magnitude() * vZ.magnitude();
	float angZ = magZ > 0.f ? std::acosf(uZ.dot(vZ) / magZ) : 0.f;
	if ((uZ.getX() * vY.getY() - uZ.getY() * vZ.getX()) < 0.f) angZ = -angZ;


	//Una vez tenemos los angulos de las rotaciones en los diferentes ejes pasamos a realizar las rotaciones
	//Para ello usamos la formula:
	// Ax' = Ax*cos(rad) - Ay*sin(rad);
	// Ay' = Ax*sin(rad) + Ay*cos(rad);
	//Esto para cada proyección en el plano de rotación y siguiendo el orden de rotación: X, Y, Z.
	//Nota: Cambiamos los signos de la operación en el eje Y para respetar la regla de la mano derecha.

	const float cx = cosf(angX), sx = sinf(angX);
	const float cy = cosf(angY), sy = sinf(angY);
	const float cz = cosf(angZ), sz = sinf(angZ);

	//PASAR A COORDENADAS LOCALES
	position.setX(position.getX() - center.getX());
	position.setY(position.getY() - center.getY());
	position.setZ(position.getZ() - center.getZ());

	//Rotación en X
	const float y1 = position.getY() * cx - position.getZ() * sx;
	const float z1 = position.getY() * sx + position.getZ() * cx;
	position.setY(y1);
	position.setZ(z1);

	// Rotación en Y
	const float x2 = position.getX() * cy + position.getZ() * sy;
	const float z2 = -position.getX() * sy + position.getZ() * cy;
	position.setX(x2);
	position.setZ(z2);

	// Rotación en Z
	const float x3 = position.getX() * cz - position.getY() * sz;
	const float y3 = position.getX() * sz + position.getY() * cz;
	position.setX(x3);
	position.setY(y3);

	//DEVOLVER A COORDENADAS GLOBALES
	position.setX(position.getX() + center.getX());
	position.setY(position.getY() + center.getY());
	position.setZ(position.getZ() + center.getZ());
}