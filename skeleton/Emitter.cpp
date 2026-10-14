

#include "Emitter.h"
#include "ParticleFactory.h"
#include "Proyectile.h"

Emitter::Emitter( ParticleFactory* factory, Vector3D<float> position, Vector3D<float> direction, float m_minVel, float m_maxVel, ParticleType type, float mean, float stdD, float freq, bool active)
 : m_factory(factory), m_position(position), m_direction(direction), m_minVel(m_minVel), m_maxVel(m_maxVel), m_type(type), m_densityFunc(UNIFORM), m_active(active), m_mean(mean), m_stdDeviation(stdD), m_freq(freq), m_currT(1.f) {
	std::random_device rd;
	m_engine.seed(rd());
}

bool Emitter::createParticle(double t) {
	if (!m_active) return false;

	while (m_currT > 0) {
		//Tenemos que crear una particula con una velocidad inicial hacia una dirección aleatoria dentro del rango.
		const float vel = newFloat(m_minVel, m_maxVel);
		const Vector3D<float> position = newPosition();
		const Vector3D<float> direction = newDirection(position).normalize();

		Vector3D<float> color = position - m_position; color = color.normalize();
		color = { abs(color.getX()), abs(color.getY()), abs(color.getZ()) };

		if (color.getX() > color.getY() && color.getX() > color.getZ()) {
			color = { 1, 0, 0 };
		}
		else if (color.getY() > color.getZ()) {
			color = { 0, 1, 0 };
		}
		else {
			color = { 0, 0, 1 };
		}

		switch (m_type) {
		case PROYECTILE:
			m_factory->addParticle(new Proyectile(position, direction * vel, 0.005f, 0.5f, { color.getX(), color.getY(), color.getZ(), 1.f }));
		default:break;
		}

		m_currT -= 1.f / m_freq;
	}

	m_currT += 1;

	return true;
}

float Emitter::uniformRandom(float open_min, float close_max) {
	std::uniform_real_distribution<float> m_uniform;
	m_uniform = std::uniform_real_distribution<float>(open_min, close_max);

	return m_uniform(m_engine);
}

float Emitter::normalRandom(float open_min, float open_max, float mean, float stdDeviation) {
	std::normal_distribution<float> m_normal; int valor;

	m_normal = std::normal_distribution<float>(mean, stdDeviation);
	do {
		valor = m_normal(m_engine);
	} while (valor < open_min || valor > open_max);

	return valor;
}

float Emitter::newFloat(float min, float max) {
	float value;

	switch (m_densityFunc) {
	case UNIFORM: value = uniformRandom(min, max); break;
	case NORMAL: value = normalRandom(min, max, m_mean, m_stdDeviation); break;
	default: value = 0; break;
	}

	return value;
}

void Emitter::rotatePoint(
	Vector3D<float>& position,
	const Vector3D<float>& u, const Vector3D<float>& v,
	const Vector3D<float>& center) {

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