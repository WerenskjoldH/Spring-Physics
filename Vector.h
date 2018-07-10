#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>
#include <iostream>

namespace rn{

	class vector3f {
	private:

	public:
		float x;
		float y;
		float z;

		// Constructors
		vector3f(float iX = 0, float iY = 0, float iZ = 0) : x(iX), y(iY), z(iZ) {};

		// Deconstructor
		~vector3f() {}

		// Copy Constructor
		vector3f(const vector3f & v) : x(v.x), y(v.y), z(v.z) {};

		// Operator Overloads
		vector3f& operator=(const vector3f & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		void operator+=(const vector3f & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const vector3f & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const float & s)
		{
			x *= s;
			y *= s;
			z *= s;
		}

		void operator/=(const float & s)
		{
			x = x / s;
			y = y / s;
			z = z / s;
		}

		float operator*(const vector3f & v) const
		{
			return x*v.x + y*v.y + z*v.z;
		}

		vector3f operator/(const float s) const
		{
			return vector3f(x / s, y / s, z / s);
		}

		vector3f operator*(const float s) const
		{
			return vector3f(s*x, s*y, x*z);
		}

		vector3f operator-(const vector3f & v) const
		{
			return vector3f(x - v.x, y - v.y, z - v.z);
		}

		vector3f operator+(const vector3f & v) const
		{
			return vector3f(x+v.x, y+v.y, z+v.z);
		}

		vector3f cross(const vector3f & v) const
		{
			return vector3f(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
		}

		vector3f unit()
		{
			return vector3f(*this/this->magnitude());
		}

		void normalize()
		{
			(*this) = (*this).unit();
		}

		float angleBetweenVector(vector3f & v)
		{
			return std::acos(v * (*this) / v.magnitude() * this->magnitude());
		}

		float magnitude()
		{
			return std::sqrtf(x*x + y * y + z * z);
		}
	};

	class vector4f {
	private:

	public:
		float x;
		float y;
		float z;
		float w;

		// Constructors
		vector4f() : x(0.f), y(0.f), z(0.f), w(1.f) {};
		vector4f(float iX = 0, float iY = 0, float iZ = 0, float iW = 1) : x(iX), y(iY), z(iZ), w(iW) {};

		// Deconstructor
		~vector4f() {}

		// Copy Constructor
		vector4f(const vector4f & v) : x(v.x), y(v.y), z(v.z), w(v.w) {};

		// Operator Overloads
		vector4f& operator=(const vector4f & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;

			return *this;
		}

		void operator+=(const vector4f & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}

		void operator-=(const vector4f & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}

		void operator*=(const float & s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}

		void operator/=(const float & s)
		{
			x = x / s;
			y = y / s;
			z = z / s;
			w = w / s;
		}

		float operator*(const vector4f & v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		vector4f operator/(const float s) const
		{
			return vector4f(x / s, y / s, z / s, w / s);
		}

		vector4f operator*(const float s) const
		{
			return vector4f(s*x, s*y, x*z, w*z);
		}

		vector4f operator-(const vector4f & v) const
		{
			return vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		vector4f operator+(const vector4f & v) const
		{
			return vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		vector4f unit()
		{
			return vector4f(*this / this->magnitude());
		}

		void normalize()
		{
			(*this) = (*this).unit();
		}

		float angleBetweenVector(vector4f & v)
		{
			return std::acos(v * (*this) / v.magnitude() * this->magnitude());
		}

		float magnitude()
		{
			return std::sqrtf(x*x + y * y + z * z + w * w);
		}
	};

}

#endif