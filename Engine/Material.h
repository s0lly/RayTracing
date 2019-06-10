#pragma once

#include "Hitable.h"

static Vec3 RandomUnitInSphere()
{
	Vec3 p;

	do
	{
		p = Vec3(((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)), ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1))) * 2.0f - Vec3(1.0f, 1.0f, 1.0f);

	} while (p.lengthSqrd() >= 1.0f);

	return p;
}

static Vec3 Reflect(Vec3 &v, Vec3 n)
{
	return v -  n * v.Dot(n) * 2.0f;
}



struct Material
{
	virtual bool scatter(Ray &r_in, HitRecord &rec, Vec3 &attenuation, Ray &scattered) = 0;
};


struct Lambertian : public Material
{
	// Data
	Vec3 albedo;



	// Functions

	Lambertian(Vec3 &a) : albedo(a) {}
	virtual bool scatter(Ray &r_in, HitRecord &rec, Vec3 &attenuation, Ray &scattered)
	{
		Vec3 target = rec.p + rec.normal + RandomUnitInSphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};


struct Metal : public Material
{
	// Data
	Vec3 albedo;
	float fuzziness;


	// Functions

	Metal(Vec3 &a, float f) : albedo(a) { fuzziness = f < 1.0f ? f : 1.0f; }
	virtual bool scatter(Ray &r_in, HitRecord &rec, Vec3 &attenuation, Ray &scattered)
	{
		Vec3 reflected = Reflect(r_in.Direction().GetNormalized(), rec.normal);
		scattered = Ray(rec.p, reflected + RandomUnitInSphere() * fuzziness);
		attenuation = albedo;
		return (scattered.Direction().Dot(rec.normal) > 0.0f);
	}
};


