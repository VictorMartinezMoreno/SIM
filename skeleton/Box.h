#pragma once
#include "geometry.h"

class Box : public Geometry {
protected:
	float m_widthAir, m_heightAir, m_widthGround, m_heightGround, m_depth;

public:
	Box(Vector3D<float> pos, Vector3D<float> dir, float wA, float hA, float wG, float hG, float d) noexcept;
	virtual ~Box() = default;

	virtual bool inArea(const Vector3D<float>& pos) const override;
	virtual Vector3D<float> rdmPoint(std::function<float(float, float)> function, float depth = -1) const override;
private:
};