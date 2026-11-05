#pragma once
#include "geometry.h"

class Ellipsoid : public Geometry {
protected:
	float m_widthRadius, m_heightRadius, m_depthRadius;

public:
	Ellipsoid(Vector3D<float> pos, Vector3D<float> dir, float w, float h, float d) noexcept;
	virtual ~Ellipsoid() = default;

	virtual bool inArea(const Vector3D<float>& pos) const override;
	virtual Vector3D<float> rdmPoint(std::function<float(float, float)> function, float depth = -1) const override;
private:
};