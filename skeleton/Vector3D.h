#pragma once

#include <PxPhysicsAPI.h>

template<typename T = float>
class Vector3D {
protected:
	T x, y, z;

public:
	inline Vector3D() : x(0), y(0), z(0) {};
	inline Vector3D(T x, T y, T z) : x(x), y(y), z(z) {};
	inline Vector3D(const physx::PxVec3& v) : x(v.x), y(v.y), z(v.z) {};

	const T& getX() const { return x; }
	const T& getY() const { return y; }
	const T& getZ() const { return z; }

	float magnitude() const {return std::sqrt(x * x + y * y + z * z);}
	Vector3D normalize() const {return *this/magnitude();}

	float dot(const Vector3D& v) const {return x * v.x + y * v.y + z * v.z;}
	Vector3D cross(const Vector3D& v) const {return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };}

	Vector3D operator+(const Vector3D& otro) const {
		return { x + otro.x, y + otro.y, z + otro.z };
	}
	Vector3D operator-(const Vector3D& otro) const {
		return { x - otro.x, y - otro.y, z - otro.z };
	}
	Vector3D& operator-() const {
		return { -x, -y, -z};
	}
	Vector3D operator*(const Vector3D& otro) const {
		return { x * otro.x, y * otro.y,  z * otro.z};
	}
	Vector3D operator*(T otro) const {
		return { x * otro, y * otro, z * otro };
	}

	Vector3D& operator+=(const Vector3D& otro) {
		x += otro.x;
		y += otro.y;

		return *this;
	}
	Vector3D& operator-=(const Vector3D& otro) {
		x -= otro.x;
		y -= otro.y;

		return *this;
	}

	bool operator==(const Vector3D& v1, const Vector3D& v2) {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	template<typename U>
	operator Vector2D<U>() const {
		return { U(x), U(y) };
	}

	operator physx::PxVec3() const {
		return { x, y, z };
	}
};