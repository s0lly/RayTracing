#pragma once

#include "Ray.h"
#include "AABB.h"
#include <stdlib.h>

struct Material;






struct HitRecord
{
	float t;
	Vec3 p;
	Vec3 normal;
	Material *matPtr;
};

struct Hitable
{
	virtual void Update(float dt) = 0;
	virtual bool Hit(Ray &r, float t_min, float t_max, HitRecord &rec) = 0;
	virtual bool BoundingBox(float t0, float t1, AABB &box) = 0;
};


struct Sphere : public Hitable
{
	// Data

	Vec3 centerOld, centerCurr;
	float radius;
	Vec3 vel;
	Material *matPtr;

	// Functions

	Sphere() {}
	Sphere(Vec3 cen, float r, Material *in_matPtr, Vec3 in_vel = Vec3(0.0f, 0.0f, 0.0f)) : centerOld(cen), centerCurr(cen), radius(r), vel(in_vel), matPtr(in_matPtr) {};
	
	virtual void Update(float dt)
	{
		centerOld = centerCurr;
		centerCurr = centerOld + vel * dt;
	}

	Vec3 CenterAtTime(float t)
	{
		return centerOld + vel * t;
	}

	virtual bool Hit(Ray &r, float t_min, float t_max, HitRecord &rec)
	{
		Vec3 oc = r.Origin() - CenterAtTime(r.time);
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
				rec.normal = (rec.p - CenterAtTime(r.time)) / radius;
				rec.matPtr = matPtr;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / (a);
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.PointOnRay(rec.t);
				rec.normal = (rec.p - CenterAtTime(r.time)) / radius;
				rec.matPtr = matPtr;
				return true;
			}
		}
		return false;
	}

	bool BoundingBox(float t0, float t1, AABB &box)
	{
		AABB oldBox(centerOld - Vec3(radius, radius, radius), centerOld + Vec3(radius, radius, radius));
		AABB currBox(centerCurr - Vec3(radius, radius, radius), centerCurr + Vec3(radius, radius, radius));

		box = SurroundingBox(oldBox, currBox);

		return true;
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
	virtual void Update(float dt)
	{
		for (int i = 0; i < listSize; i++)
		{
			list[i]->Update(dt);
		}
	}
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

	bool BoundingBox(float t0, float t1, AABB &box)
	{
		if (listSize < 1)
		{
			return false;
		}
		AABB tempBox;
		bool firstTrue = list[0]->BoundingBox(t0, t1, tempBox);
		if (!firstTrue)
		{
			return false;
		}
		else
		{
			box = tempBox;
		}

		for (int i = 1; i < listSize; i++)
		{
			if (list[i]->BoundingBox(t0, t1, tempBox))
			{
				box = SurroundingBox(box, tempBox);
			}
			else
			{
				return false;
			}
		}
	}
};


struct BVHNode : public Hitable
{
	// Data

	Hitable *left;
	Hitable *right;
	AABB box;

	// Functions

	
	

	BVHNode() {}
	BVHNode(Hitable **l, int n, float time0, float time1);

	virtual bool Hit(Ray &r, float t_min, float t_max, HitRecord &rec)
	{
		if (box.hit(r, t_min, t_max))
		{
			HitRecord leftRec, rightRec;
			bool hitLeft = left->Hit(r, t_min, t_max, leftRec);
			bool hitRight = right->Hit(r, t_min, t_max, rightRec);
			if (hitLeft && hitRight)
			{
				if (leftRec.t < rightRec.t)
				{
					rec = leftRec;
				}
				else
				{
					rec = rightRec;
				}
				return true;
			}
			else if (hitLeft)
			{
				rec = leftRec;
				return true;
			}
			else if (hitRight)
			{
				rec = rightRec;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool BoundingBox(float t0, float t1, AABB &in_box)
	{
		box = in_box;
		return true;
	}

	virtual void Update(float dt)
	{

	}

};

