#pragma once
#include "Vector3D.h"
#include <functional>

class Geometry {
public:
	static void rotatePoint(
		Vector3D<float>& position,
		const Vector3D<float>& u,
		const Vector3D<float>& v,
		const Vector3D<float>& center
	);
protected:
	Vector3D<float> m_position, m_direction;
public:
	virtual bool inArea(const Vector3D<float>& point) const = 0;
	virtual Vector3D<float> rdmPoint(std::function<float(float, float)> function, float depth = -1) const = 0;

	Vector3D<float>& getPosition() noexcept { return m_position; }
	Vector3D<float>& getDirection() noexcept { return m_direction; }

	virtual ~Geometry() = default;
protected:
	Geometry(Vector3D<float> pos, Vector3D<float> dir) noexcept;
	
};