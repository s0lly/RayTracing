#pragma once

#include "Ray.h"
#include "Vec3.h"
#include <algorithm>


static float ffmin(float a, float b)
{
	return (a < b ? a : b);
}
static float ffmax(float a, float b)
{
	return (a > b ? a : b);
}


struct AABB
{
	// Data

	Vec3 minP, maxP;


	// Functions

	AABB() {}
	AABB(Vec3 &a, Vec3 &b) { minP = a; maxP = b; }

	bool hit(Ray &r, float tmin, float tmax)
	{
		for (int a = 0; a < 3; a++)
		{
			float invD = 1.0f / r.Direction()[a];
			float t0 = (minP[a] - r.Origin()[a]) * invD;
			float t1 = (maxP[a] - r.Origin()[a]) * invD;
			if (invD < 0.0f)
			{
				std::swap(t0, t1);
			}
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin)
			{
				return false;
			}
		}
		return true;
	}

};


static AABB SurroundingBox(AABB box0, AABB box1)
{
	Vec3 smallBox(ffmin(box0.minP.x(), box1.minP.x()),
		ffmin(box0.minP.y(), box1.minP.y()),
		ffmin(box0.minP.z(), box1.minP.z()));

	Vec3 bigBox(ffmin(box0.maxP.x(), box1.maxP.x()),
		ffmin(box0.maxP.y(), box1.maxP.y()),
		ffmin(box0.maxP.z(), box1.maxP.z()));

	return AABB(smallBox, bigBox);
}