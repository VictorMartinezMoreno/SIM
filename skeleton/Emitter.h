#pragma once

#include "Vector3D.h"
#include <vector>
#include <functional>
#include <random>


enum ParticleType {
	PROYECTILE
};

enum DensityFunction {
	UNIFORM,
	NORMAL
};

class ParticleFactory;

class Emitter {
protected:
	float uniformRandom(float min, float max);
	float normalRandom(float min, float max, float mean, float stdDeviation);

	float newFloat(float min, float max);
	void rotatePoint(
		Vector3D<float>& position,
		const Vector3D<float>& u,
		const Vector3D<float>& v,
		const Vector3D<float>& center
	);

	virtual Vector3D<float> newPosition() = 0;
	virtual Vector3D<float> newDirection(const Vector3D<float>& pos) = 0;
public:

	Emitter(
		ParticleFactory* factory,
		Vector3D<float> position,
		Vector3D<float> direction,
		float m_minVel, float m_maxVel,
		ParticleType type,
		float mean, float stdD,
		float freq,
		bool active
	);

	virtual bool createParticle(double t);

	inline void activate(bool activate) noexcept { m_active = activate; }
	inline bool isActive() const noexcept { return m_active; }

	inline void setDensityFunction(DensityFunction densityFunc) noexcept { m_densityFunc = densityFunc; }
	inline void setParticleType(ParticleType type) noexcept { m_type = type; }

	inline Vector3D<float>& getPos() noexcept { return m_position; }
	inline Vector3D<float>& getDir() noexcept { return m_direction; }

	inline void setMean(float mean) noexcept { m_mean = mean; }
	inline void setStdDeviation(float stdDeviation) noexcept { m_stdDeviation = stdDeviation; }
	inline void setVel(float minVel, float maxVel) noexcept { m_minVel = minVel; m_maxVel = maxVel; }
	inline void setFreq(float f) noexcept { m_freq = f; }

	inline float getMean() const noexcept { return m_mean; }
	inline float getStdDeviation() const noexcept { return m_stdDeviation; }
	inline float getMinVel() const noexcept { return m_minVel; }
	inline float getMaxVel() const noexcept { return m_maxVel; }
	inline float getFreq() const noexcept { return m_freq; }

protected:
	ParticleType m_type;
	DensityFunction m_densityFunc;
	ParticleFactory* m_factory;
	Vector3D<float> m_position, m_direction;
	float m_mean, m_stdDeviation, m_minVel, m_maxVel, m_freq, m_currT;
	bool m_active;
	std::mt19937 m_engine;
};