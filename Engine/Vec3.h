#pragma once

#include <math.h>

struct Vec3
{
	// Data

	float e[3];



	// Functions

	Vec3()
	{

	}

	Vec3(float e0, float e1, float e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	inline float x() { return e[0]; }
	inline float y() { return e[1]; }
	inline float z() { return e[2]; }
	inline float r() { return e[0]; }
	inline float g() { return e[1]; }
	inline float b() { return e[2]; }

	inline Vec3 operator +() { return *this; }
	inline Vec3 operator -() { return { -e[0], -e[1], -e[2] }; }
	inline float& operator [] (int i) { return e[i]; }

	inline Vec3& operator+=(Vec3 rhs)
	{
		e[0] += rhs[0];
		e[1] += rhs[1];
		e[2] += rhs[2];

		return *this;
	}
	inline Vec3& operator-=(Vec3 rhs)
	{
		e[0] -= rhs[0];
		e[1] -= rhs[1];
		e[2] -= rhs[2];

		return *this;
	}
	inline Vec3& operator*=(Vec3 rhs)
	{
		e[0] *= rhs[0];
		e[1] *= rhs[1];
		e[2] *= rhs[2];

		return *this;
	}
	inline Vec3& operator/=(Vec3 rhs)
	{
		e[0] /= rhs[0];
		e[1] /= rhs[1];
		e[2] /= rhs[2];

		return *this;
	}
	inline Vec3 operator+(Vec3 rhs)
	{
		return { e[0] + rhs[0], e[1] + rhs[1], e[2] + rhs[2] };
	}
	inline Vec3 operator-(Vec3 rhs)
	{
		return { e[0] - rhs[0], e[1] - rhs[1], e[2] - rhs[2] };
	}
	inline Vec3 operator*(Vec3 rhs)
	{
		return { e[0] * rhs[0], e[1] * rhs[1], e[2] * rhs[2] };
	}
	inline Vec3 operator/(Vec3 rhs)
	{
		return { e[0] / rhs[0], e[1] / rhs[1], e[2] / rhs[2] };
	}

	inline Vec3& operator*=(float rhs)
	{
		e[0] *= rhs;
		e[1] *= rhs;
		e[2] *= rhs;

		return *this;
	}
	inline Vec3& operator/=(float rhs)
	{
		float k = 1.0f / rhs;

		e[0] *= k;
		e[1] *= k;
		e[2] *= k;

		return *this;
	}
	inline Vec3 operator*(float rhs)
	{
		return { e[0] * rhs , e[1] * rhs , e[2] * rhs };
	}
	inline Vec3 operator/(float rhs)
	{
		float k = 1.0f / rhs;
		return { e[0] * k , e[1] * k , e[2] * k };
	}

	inline float lengthSqrd()
	{
		return (x() * x() + y() * y() + z() * z());
	}
	inline float length()
	{
		return sqrt(lengthSqrd());
	}
	

	inline Vec3 GetNormalized()
	{
		return (*this / length());
	}

	inline float Dot(Vec3& rhs)
	{
		return (x() * rhs.x() + y() * rhs.y() + z() * rhs.z());
	}

	inline Vec3 Cross(Vec3& rhs)
	{
		return {y() * rhs.z() - z() * rhs.y(),
				z() * rhs.x() - x() * rhs.z(),
				x() * rhs.y() - y() * rhs.x()};
	}

};