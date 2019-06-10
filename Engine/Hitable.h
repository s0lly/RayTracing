#pragma once

#include "Ray.h"

struct HitRecord
{
	float t;
	Vec3 p;
	Vec3 normal;
};

struct Hitable
{
	virtual bool Hit(Ray &r, float t_min, float t_max, HitRecord &rec) = 0;
};


struct Sphere : public Hitable
{
	// Data

	Vec3 center;
	float radius;


	// Functions

	Sphere() {}
	Sphere(Vec3 cen, float r) : center(cen), radius(r) {};
	virtual bool Hit(Ray &r, float t_min, float t_max, HitRecord &rec)
	{
		Vec3 oc = r.Origin() - center;
		float a = r.Direction().Dot(r.Direction());
		float b = oc.Dot(r.Direction());
		float c = oc.Dot(oc) - radius * radius;
		float discriminant = b * b - a * c;

		if (discriminant > 0.0f)
		{
			float temp = (-b - sqrt(discriminant)) / ( a);
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.PointOnRay(rec.t);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / (a);
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.PointOnRay(rec.t);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
		}
		return false;
	}
};


struct HitableList : public Hitable
{
	// Data

	Hitable **list;
	int listSize;


	// Functions

	HitableList() {}
	HitableList(Hitable **l, int n) { list = l; listSize = n; }
	virtual bool Hit(Ray &r, float t_min, float t_max, HitRecord &rec)
	{
		HitRecord tempRec;
		bool hitAnything = false;
		double closestSoFar = t_max;
		for (int i = 0; i < listSize; i++)
		{
			if (list[i]->Hit(r, t_min, closestSoFar, tempRec))
			{
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			}
		}
		return hitAnything;
	}
};