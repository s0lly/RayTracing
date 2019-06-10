#pragma once

#include "Vec3.h"

struct Ray
{
	// Data

	Vec3 a;
	Vec3 b;


	// Functions

	Ray() {}

	Ray(Vec3& in_a, Vec3& in_b)
	{
		a = in_a;
		b = in_b;
	}

	Vec3 Origin() {return a;};
	Vec3 Direction() { return b; };
	Vec3 PointOnRay(float t) { return (a + b * t); };

	


};
