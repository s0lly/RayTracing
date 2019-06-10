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

static bool Refract(Vec3 &v, Vec3 &n, float niOverNt, Vec3 &refractored)
{
	Vec3 uv = v.GetNormalized();
	float dt = uv.Dot(n);
	float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);
	if (discriminant > 0.0f)
	{
		refractored = (uv - n * dt) * niOverNt - n * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

static float Schlick(float cos, float ref_idx)
{
	float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * pow((1.0f - cos), 5.0f);
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


struct Dielectric : public Material
{
	// Data
	float ref_idx;


	// Functions

	Dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(Ray &r_in, HitRecord &rec, Vec3 &attenuation, Ray &scattered)
	{
		Vec3 outwardNormal;
		Vec3 reflected = Reflect(r_in.Direction(), rec.normal);
		float niOverNt;
		attenuation = Vec3(1.0f, 1.0f, 1.0f);
		Vec3 refracted;
		float reflectProb;
		float cos;

		if (r_in.Direction().Dot(rec.normal) > 0.0f)
		{
			outwardNormal = -rec.normal;
			niOverNt = ref_idx;
			cos = r_in.Direction().Dot(rec.normal) * ref_idx / r_in.Direction().length();
		}
		else
		{
			outwardNormal = rec.normal;
			niOverNt = 1.0f /	ref_idx;
			cos = -r_in.Direction().Dot(rec.normal) / r_in.Direction().length();
		}
		if (Refract(r_in.Direction(), outwardNormal, niOverNt, refracted))
		{
			reflectProb = Schlick(cos, ref_idx);
		}
		else
		{
			//scattered = Ray(rec.p, refracted);
			reflectProb = 1.0f;
		}
		if (((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)) < reflectProb)
		{
			scattered = Ray(rec.p, reflected);
		}
		else
		{
			scattered = Ray(rec.p, refracted);
		}
		return true;
	}
};


